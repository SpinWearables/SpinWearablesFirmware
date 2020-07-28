/// # Dancing with Color: Create colorful snake that changes with rotation.
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

// Instructions in a loop function are repeated over and over again,
// in other words, "in a loop".
void loop() {
// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data.
  SpinWheel.readIMU();

// Use an **if statement** to check to see if the rotation is
// large enough. If the rotation is large enough, then 
// `SpinWheel.snake()` creates a snake-like pattern 
// on the device. Here we use (0,255,0) to make the 
// snake green, but you can use any color you like. 
  if (abs(SpinWheel.gx) > 1) { 
     SpinWheel.snake(0,255,0);
  }

  
  SpinWheel.setLargeLEDsUniform(100, 0, 0);

  // Make the SpinWheel show the registered color.
  SpinWheel.drawFrame();
}
  
