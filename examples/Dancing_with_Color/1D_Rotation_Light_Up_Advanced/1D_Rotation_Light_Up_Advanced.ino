/// # Dancing with Color: Color changes based on direction.  
///
/// In this example, we will step through the code used
/// to make the SpinWheel change color based on the direction
/// of the spin. For more information and previous examples, 
/// refer to the [dancing companion page](https://spinwearables.com/dancing/). 
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
  // Initialize all of the hardware on the SpinWheel.
  SpinWheel.begin();
}


// Here, we initialize two variables, 
// one to tell the SpinWheel what color to display
// when the device is spun in the positive direction
// and the other for the negative direction. 
int pos_spin = 0;
int neg_spin = 0;

// Instructions in a loop function are repeated over and over again,
// in other words, "in a loop".
void loop() {

// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data.
  SpinWheel.readIMU();
  
// Here, we will also utilize `else if` 
// and `else` commands. These commands are used in
// programming along with an **if statement**
// to tell the program what to do when the if condition
// is not met. In this example, our **if condition**
// checks whether or not the rotation is big enough in
// the **positive direction**. If this condition is true
// we will light up the LEDs according to the given
// instruction. Feel free to play around with this number.
  if (SpinWheel.gx > 100) {
    pos_spin = 255;
    neg_spin = 0;
  }
// If the rotation is not big enough in the 
// positive direction, we will use an `else if`
// command to see if the spin is large enough 
// in the **negative direction**. If it is, 
// then we will follow the given instruction.
  else if (SpinWheel.gx < -100) {
    neg_spin = 255;
    pos_spin = 0;
  }
// If all previous conditions are not true, 
// then we will use an `else` command. In this 
// case, if the rotation is not large enough in 
// either direction, the SpinWheel will not light up. 
  else {
    pos_spin = 0;
    neg_spin = 0;
  }
// As before, the `setLargeLEDsUniform` function tells the
// SpinWheel to show the color we would like it to show.
// Based on the previous if statements, if the device is 
// spinning in the positive direction, the LEDs will light up 
// green. If the device is spinning in the negative direction
// the LEDs will light up blue. 
  SpinWheel.setLargeLEDsUniform(0, pos_spin, neg_spin);

  SpinWheel.drawFrame();
 }
