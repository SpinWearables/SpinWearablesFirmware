/// # Dancing with Color: Have the SpinWheel respond to both acceleration and rotation. 
///
/// Here we include one final code example. This example is designed
/// to be more complex than the previous examples and to inspire
/// future work. For more information and other examples, 
/// [click here](https://spinwearables.com/dancing/).
//

// These include statements should look familiar!
// As a reminder, they allow the program to access
// coding tools for the SpinWheel.
#include "SpinWearables.h"
using namespace SpinWearables;

// The setup function should also seem familiar.
// As a reminder, the `setup` function is run once when
// the SpinWheel turns on. Also, `SpinWheel.begin()`
// prepares the LED to accept new colors.
void setup() {
  SpinWheel.begin();
}


int offset = 0;
int colorChange;

// Instructions in a loop function are repeated over and over again,
// in other words, "in a loop".
void loop() {
// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data.
  SpinWheel.readIMU();
// Here, we use an **if statement** to check if 
// the rotation is fast. If this is true, then add 
// a step to the offset.
  if (abs(SpinWheel.gx) > 1) {
    offset = SpinWheel.gx*100; 
    Serial.println(offset);
  }

// Here we will use a **for loop**. Similar to the 
// `loop` function, instructions inside the for loop
// repeat. In this case the insturctions inside the 
// for loop will repeat four times as specified by the 
// `i < 4`. This will make a rainbow in the large LEDs
// with a color change specified by the movement of the 
// device. 
  for (int i=0; i<4; i++) {
    colorChange = offset+i*255/4;
    Serial.println(colorChange);
    SpinWheel.setLargeLED(i, colorWheel(colorChange));
    SpinWheel.setLargeLED(7-i, colorWheel(colorChange));
  }

// Here we define the total acceleration as the 
// sum of the acceleration in the x,y,and z directions.
  float total_acceleration = SpinWheel.ax + SpinWheel.ay + SpinWheel.az;
  
// Here we use an **if statement** to check to see if the 
// the total acceleration is large enough. If it is, 
// then we will create a snake on the small LEDs using
// `SpinWheel.snake()`. Here we use (0,255,0) to make the 
// snake green, but you can use any color you like! 
  if (abs(total_acceleration) > 1) { 
     SpinWheel.snake(0,255,0);
  }



  SpinWheel.drawFrame();
}
