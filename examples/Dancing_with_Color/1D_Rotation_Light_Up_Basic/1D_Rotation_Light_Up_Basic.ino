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
  // change the color of the big LEDs
  if (abs(SpinWheel.gx) > 1) {
    spinning = 255;
  }

  SpinWheel.setLargeLEDsUniform(0, spinning, spinning);
  // Make the SpinWheel show the registered color.
  // If spinning fast enough, the LEDs  will be set to (0, 255, 255).
  // This is a light blue color
  SpinWheel.drawFrame();
 }
  
