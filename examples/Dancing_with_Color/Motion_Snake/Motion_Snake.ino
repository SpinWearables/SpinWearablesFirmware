/// # Dancing with Color: Create colorful snake that changes with rotation.
/// For more examples and information, refer to the [dancing companion page](https://spinwearables.com/dancing/).
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
int angle = 0; 
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
// of the device. Experiment with changing the `100` threshold
// value if you want to make the SpinWheel more or less
// sensitive. Keep in mind that `gy` measures rotation around
// the y axis, i.e. spinning in place while hanging the SpinWheel
// by the keyring.
  if (abs(SpinWheel.gy) > 100) {
     // Add 10 to make it spin at a reasonable speed.
     // Experiment with this number to change the rate
     // with which the snake spins. Can you make the 
     // snake go the other way? (Hint: what happens if you
     // subtract 10 instead?)
     angle = angle+10;
     // Here we use (0,255,0) to make the 
     // snake green, but you can use any color you like. 
     SpinWheel.setSmallLEDsPointer(angle, 0, 255, 0);
  }
// Create a pattern on the large LEDs as well. 
  SpinWheel.setLargeLEDsUniform(100, 0, 100);
// Have the SpinWheel draw the desired pattern.
  SpinWheel.drawFrame();
}
  
