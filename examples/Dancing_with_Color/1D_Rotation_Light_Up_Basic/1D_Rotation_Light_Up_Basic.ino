/// # Dancing with Color: Changing color in response to rotation in the x-direction.
///
/// Here we go through in detail how to change the color of the SpinWheel in 
/// response to the rotation of the device. For more information and other 
/// examples, refer to the [dancing companion page](https://spinwearables.com/dancing/).
//

// You've probably seen these `include` statements in some of the other code examples. 
// They allow the program to access a set of tools for the SpinWheel for us to use. 
#include "SpinWearables.h"
using namespace SpinWearables;

// The instructions we write in the `setup` block are executed
// once when the SpinWheel device powers on. We run one single instruction
// called `SpinWheel.begin()` which prepares all the LEDs to accept new colors.
void setup() {
  SpinWheel.begin();
}

// Instructions in a loop function are repeated over and over again, 
// in other words, "in a loop".
void loop() {
 

// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data, which we will
// use below to change the color.  
  SpinWheel.readIMU();

// Below we will use an **if/else statement**.
// "If" statements are vital tools in programming.
// Essentially, **if** a condition is true, we will 
// follow the given instruction.  
// In this case, if the x rotation (gx) is large enough,
// then we will change the color of the large LEDS
// by changing the `spinning` variable. 
// We picked 100 degrees per second because that made
// it turn on without decting too small motions.
// However, you can make this more or less sensitve.
// The `abs` function makes it so that the direction 
// of the rotation (clockwise or counter clockwise), 
// does not matter. 
  if (abs(SpinWheel.gx) > 100) {
// As before, the `setLargeLEDsUniform` function tells the 
// SpinWheel to show the color we would like it to show. 
// We will use (0,255,255), which is a light blue.
    SpinWheel.setLargeLEDsUniform(0, 255, 255);
  }
  else {
// Since no motion has been detected, we will instead use 
// (0,0,0), which turns off the LEDs.
    SpinWheel.setLargeLEDsUniform(0, 0, 0);
  }

// Finally, we need to tell the SpinWheel to light up the LEDs
// according to the instructions in `setLargeLEDsUniform`.
  SpinWheel.drawFrame();
 }
  
