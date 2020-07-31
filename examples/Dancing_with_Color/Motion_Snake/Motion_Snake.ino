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
// Initialize the angle variable to zero. This will keep
// track of the Spin Wheel's rotation.
uint8_t angle = 0; 
// Instructions in a loop function are repeated over and over again,
// in other words, "in a loop".
void loop() {
// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data.
  SpinWheel.readIMU();

// Use an **if statement** to check to see if the rotation is
// large enough. If the rotation is large enough, then 
// we will create a snake-like pattern on the device
// where the motion of the snake is based on the motion 
// of the device.  We add 5 to have the snake spin
// at a reasonable speed. You can adjust this number
// to change the speed at which the snake rotates.
// Here we use (0,255,0) to make the 
// snake green, but you can use any color you like. 
  if (abs(SpinWheel.gx) >= 1) { 
     angle = angle + SpinWheel.gx + 5;
     setSmallLEDsPointer(angle, 0, 255, 0);
  }
// Create a pattern on the large LEDs as well. 
  SpinWheel.setLargeLEDsUniform(100, 0, 100);
// Have the SpinWheel draw the desired pattern.
  SpinWheel.drawFrame();
}
  
