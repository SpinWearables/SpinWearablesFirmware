/// # Dancing with Color: Step x, changing color in response to rotation 
// in the z-direction
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // Initialize all of the hardware on the SpinWheel.
  SpinWheel.begin();
}


void loop() {
  // define a variable that stores 
  int spinning = 0;
  
  SpinWheel.readIMU();
  // If the x rotation (gx) is big enough, then 
  // change the color of the big LEDs based on the
  // direction of the spin
  if (abs(SpinWheel.gx) > 1) {
    spinning = 255;
  }

  // If gz is positive, set the big LEDs to light up green
  // If gz is negative, set the big LEDs to light up blue
  SpinWheel.setLargeLEDsUniform(0, spinning, spinning);
  // Make the SpinWheel show the registered color.
  SpinWheel.drawFrame();
 }
  
