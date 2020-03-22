/// Implementing an Arduino Recurrent Neural Network
//

// #### Linear Algebra Helpers
//--
// $\vec{\textrm{out}} = m\cdot\vec{\textrm{in}}$, matrix-vector multiplication
void matvecmul(float m[], float in[], float out[], size_t s_in, size_t s_out) {
  for (size_t i=0; i<s_out; i++) {
    out[i] = 0;
    for (size_t j=0; j<s_in; j++) {
      out[i] += m[i*s_in+j]*in[j];
    }
  }  
}

// $\vec{\textrm{out}} = \vec{\textrm{out}} + m\cdot\vec{\textrm{in}}$, matrix-vector multiplication with accumulation
void matvecmulacc(float m[], float in[], float out[], size_t s_in, size_t s_out) {
  for (size_t i=0; i<s_out; i++) {
    for (size_t j=0; j<s_in; j++) {
      out[i] += m[i*s_in+j]*in[j];
    }  
  }
}

// $\vec{\textrm{out}} = \vec{\textrm{a}} + \vec{\textrm{b}}$, vector-vector addition
void vecvecadd(float a[], float b[], float out[], size_t s) {
  for (size_t i=0; i<s; i++) {
    out[i] = a[i]+b[i];
  }  
}

// $\vec{\textrm{out}} = \vec{\textrm{out}} + \vec{\textrm{a}}$, vector-vector addition with accumulation
void vecvecaddinplace(float a[], float out[], size_t s) {
  for (size_t i=0; i<s; i++) {
    out[i] += a[i];
  }  
}

// $\vec{\textrm{out}} = \vec{\textrm{a}}$, copying a vector
void veccopy(float a[], float out[], size_t s) {
  for (size_t i=0; i<s; i++) {
    out[i] = a[i];
  }  
}

// $\vec{\textrm{out}} = \textrm{relu}(\vec{\textrm{a}})$, applying the $\textrm{relu}$ function to every element of a vector. `RELU_MAX` is used to ensure that erroneous large values are trimmed and do not cause an overflow later in the computation. 
// $\textrm{relu}(x) = \begin{cases}
//    x & \text{if } x > 0, \\
//    0 & \text{otherwise}.
// \end{cases}$
#define RELU_MAX 30
void relu(float a[], float out[], size_t s) {
  for (size_t i=0; i<s; i++) {
    if (a[i]>0) {
      out[i] = a[i];
      if (a[i]>RELU_MAX) {out[i]=RELU_MAX;}
    }
    else {out[i] = 0;}
  }    
}

// $\vec{\textrm{a}} = \textrm{relu}(\vec{\textrm{a}})$, applying the $\textrm{relu}$ function inplace
void reluinplace(float a[], size_t s) {
  for (size_t i=0; i<s; i++) {
    if (a[i]>0) {
      if (a[i]>RELU_MAX) {a[i]=RELU_MAX;}
    }
    else {a[i] = 0;}
  }    
}

// $\vec{\textrm{a}} = \textrm{softmax}(\vec{\textrm{a}})$, where $\sigma(\vec{x})_i = \frac{e^{x_i}}{\sum_{j=1}^K e^{x_j}}$ for $\vec{x}=(x_1,\dotsc,x_K)$.
void softmaxinplace(float a[], size_t s) {
  float sum = 0;
  for (size_t i=0; i<s; i++) {
    a[i] = exp(a[i]);
    sum += a[i];
  }    
  for (size_t i=0; i<s; i++) {
    a[i] /= sum;
  }      
}


// #### Specifying the size of our two-layer recurrent neural network
const size_t neurons_in  = 6; // input dimensions (3 acceleration and 3 rotation components)
const size_t neurons_1s  = 6; // first RNN memory size
const size_t neurons_1o  = 6; // first RNN output size
const size_t neurons_2s  = 6; // second RNN
const size_t neurons_2o  = 6; // ...
const size_t neurons_out = 3; // output dimensions (number of possible gestures)


// #### The data structures used to store the parameters for our recurrent neural network
float W1s[neurons_1s*neurons_in] = { 0.5321287, 0.6107104, 1.3286344, -0.6015093, 0.56184286, -0.050672613, -0.28946915, -0.57202274, 0.5797093, 0.10561681, 1.7290003, -0.68493843, -0.18255526, -0.37313738, 1.2256309, -0.1742842, 0.6492496, -0.16173245, -0.9695452, -0.5891188, -0.013323135, 0.6650615, 0.42116144, -0.59877527, 0.058546405, -0.71124023, -0.4949681, 0.026260667, 0.47205865, 0.017517323, 0.44564795, -0.76846886, 0.6713811, -1.7036608, 0.06296093, 0.27191502 };
float U1 [neurons_1s*neurons_1s] = { 0.08446167, 2.1222587, -0.262183, 0.041411262, 0.092383526, -1.0871025, 0.765727, -1.2816284, -0.79608244, 1.0392288, 0.05335982, 0.04486225, 0.046529382, -1.4757994, 0.13218978, 0.0464745, -0.06651882, -0.8113239, 2.010752, 0.27113342, -0.082562454, 0.36493123, -1.3630337, 1.5551832, -1.8181484, -0.21996354, -0.60703295, -0.20818894, 0.12968491, 1.1444167, -1.0321264, -0.71735334, -0.4447773, 0.25020576, 0.4118029, -1.9402288 };
float W1o[neurons_1o*neurons_1s] = { 0.13802966, -1.2219762, 0.058708522, 0.1777648, 1.6724335, -1.4119003, -0.032558057, 0.44839227, 0.40060967, 0.64469165, -0.29333997, -0.025161164, -0.2800877, -0.902683, -0.007265689, 0.54415846, 0.66456676, -0.77940935, 0.37354767, 0.3158186, -0.6347513, 0.17989126, -0.22734974, -0.49951622, -0.5184792, 0.87216437, 2.159849, -0.6910299, -0.08984194, 0.032428134, 0.13159314, -0.88068604, 0.47105592, 0.12390203, -0.3439282, 0.4603399 };
float B1s[neurons_1s] = { -1.105348, 0.00018683162, -0.02873229, -0.06346775, -0.17056179, 0.09518265 };
float B1o[neurons_1o] = { 0.34591475, -0.14795464, 0.2325652, -0.10135709, -1.3309003, 0.44049194 };
float W2s[neurons_2s*neurons_1o] = { -0.47867066, -2.0650294, -0.09539489, -0.36280107, 1.3170956, 0.029860241, -0.27149627, 0.58525115, -0.10355578, -0.44423324, 0.232523, -0.6986958, 0.082030736, 0.055767298, -0.04935323, -0.28878313, 0.066991135, -0.15354092, 0.094942436, -1.6132945, 0.036912344, 0.29851636, 1.2205178, -0.7134117, -1.2386477, -0.5278449, -0.19041571, 0.048836123, -0.12733762, 0.03632712, 2.8797266, 0.61762565, 0.053293455, -0.34995812, 0.3548257, 0.8126559 };
float U2 [neurons_2s*neurons_2s] = { -0.15002497, -0.7135592, -0.685698, 0.19555788, -0.9222942, 0.60537004, 0.20041735, -0.015652642, 0.2094619, -0.061256256, 0.020260328, 1.1851788, 0.0739529, 0.016536528, 0.0017053923, -0.001012617, 0.4333541, 2.0129955e-05, -0.20776315, 0.34800503, 1.2278594, -0.2840473, 1.6044365, 0.11292993, 1.2254378, 2.0934033, -1.8157494, 0.21263774, -0.009304846, -0.13362795, 1.1646845, -0.19165255, 0.011544819, 1.0697566, 0.43793356, 0.09747889 };
float W2o[neurons_2o*neurons_2s] = { 0.014649042, -0.06266459, 0.00044530613, -0.8122457, -0.36646405, -0.0798095, 0.3709301, 0.37230963, 3.8917642e-05, -0.0005861422, 0.2968952, 1.5582066, -1.3202109e-05, 1.799133, -1.5939819e-05, 0.10810138, 2.5070357, 0.2853145, -1.0321325, 0.0011201913, 1.5661702e-05, -0.058740117, 0.00024601142, 0.19350934, -0.00044874512, 0.7337828, 5.3875847e-06, 0.06492587, 2.9979377, -0.56943846, 0.00037777785, -0.00025590323, -0.0010820613, 4.989095e-06, 0.0007219418, -0.0005042125 };
float B2s[neurons_2s] = { -0.028206171, 0.5156735, 6.478218e-05, 1.2108356, -0.31679368, -0.024533587 };
float B2o[neurons_2o] = { 1.4028785, 0.0001855492, -0.1894923, 0.103634566, -0.113036916, -0.0009970091 };
float Wout[neurons_out*neurons_1o] = { -1.5629566, 0.4279106, 0.21059136, 0.0009926992, 0.1298369, 0.00050598645, 2.0700727, 0.19776538, 0.18575023, 0.48138946, 0.9464396, -0.00084920716, 0.053360283, -0.36190554, -1.7918297, -1.6159785e-05, -0.5657281, 8.879579e-06 };
float Bout[neurons_out] = { -1.3225704, 3.2274518e-05, 2.5265179 };


// #### Global arrays in which to store the input and output vectors, as well as intermediary states
float input[neurons_in];
float state1[neurons_1s];
float state1_tmp[neurons_1s];
float hidden1[neurons_1o];
float state2[neurons_2s];
float state2_tmp[neurons_2s];
float hidden2[neurons_2o];
float output[neurons_out];


// #### The actual neural network
size_t network() {
// First RNN layer
// $\vec{s}_1 \leftarrow \sigma(W_{1s}\cdot\vec{s}_1+U_1\cdot\vec{v}_\textrm{in}+\vec{b}_{1r})$
  matvecmul   (U1  , input  , state1_tmp, neurons_in, neurons_1s);
  matvecmulacc(W1s , state1 , state1_tmp, neurons_1s, neurons_1s);
  vecvecaddinplace(B1s, state1_tmp, neurons_1s);
  relu(state1_tmp, state1, neurons_1s);
  
// $\vec{v}_\textrm{rec1} \leftarrow \sigma(W_{1o}\cdot\vec{s}_1+\vec{b}_{1o})$
  matvecmul   (W1o , state1 , hidden1   , neurons_1s, neurons_1o);
  vecvecaddinplace(B1o, hidden1, neurons_1o);
  reluinplace(hidden1, neurons_1o);

// Second RNN layer
// $\vec{s}_2 \leftarrow \sigma(W_{2s}\cdot\vec{s}_2+U_1\cdot\vec{v}_\textrm{rec1}+\vec{b}_{2r})$
  matvecmul   (U2  , hidden1, state2_tmp, neurons_1o, neurons_2s);
  matvecmulacc(W2s , state2 , state2_tmp, neurons_2s, neurons_2s);
  vecvecaddinplace(B2s, state2_tmp, neurons_2s);
  relu(state2_tmp, state2, neurons_2s);
  
// $\vec{v}_\textrm{rec2} \leftarrow \sigma(W_{2o}\cdot\vec{s}_2+\vec{b}_{2o})$
  matvecmul   (W2o , state2 , hidden2   , neurons_2s, neurons_2o);
  vecvecaddinplace(B2o, hidden2, neurons_2o);
  reluinplace(hidden2, neurons_2o);
  
// Final decision layer
// $\vec{v}_\textrm{out} \leftarrow \textrm{softmax}(W\cdot\vec{v}_\textrm{rec2}+\vec{b})$
  matvecmul   (Wout, hidden2, output    , neurons_2o, neurons_out);
  vecvecaddinplace(Bout, output, neurons_out);
  softmaxinplace(output, neurons_out);

// Find and return the most "probable" gesture, i.e. the one with the largest
// component in the `output` vector.
  size_t c = 0;
  for (size_t i=0; i<neurons_out; i++) {
    if (output[i]>output[c]) {
      c=i;
    }
  }
  return c;
}
