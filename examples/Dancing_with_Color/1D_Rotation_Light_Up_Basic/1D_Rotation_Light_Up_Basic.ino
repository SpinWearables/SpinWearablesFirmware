/// # Dancing with Color: Step x, changing color in response to rotation in the z-direction.

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
//
//
//
// Insturctions in a loop function are repeated over and over again, 
// in other words, "in a loop".
void loop() {
// Here we get to the code specific to this example.
// First we will initialize a variable which stores 
// a number that tells the SpinWheel what color to display. . 
// In the code below we will choose this color based on the 
// motion of the SpinWheel itself. 
  int spinning = 0;
 
// 
// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data, which we will
// use below to change the color.  
  SpinWheel.readIMU();

// Below we will use an **if/else statement**.
// Ife statements are vital tools in programming.
// Essentially, **if** a condition is true, we will 
// follow the given instruction.  
// In this case, if the x rotation (gx) is large enough,
// then we will change the color of the large LEDS
// by changing the `spinning` variable. The `abs` function 
// makes it so that the direction of the rotation
// (clockwise or counter clockwise), does not matter. 
  if (abs(SpinWheel.gx) > 1) {
    spinning = 255;
  }

// As before, the `setLargeLEDsUniform` function tells the 
// SpinWheel to show the color we would like it to show. 
// In this case, if the SpinWheel is spinning, we will use
// (0,255,255), which is a light blue. 
  SpinWheel.setLargeLEDsUniform(0, spinning, spinning);
  SpinWheel.drawFrame();
 }
  
//
