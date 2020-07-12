/// # Dancing with Color: Step x, changing color in response to rotation 
// in each direction
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // Initialize all of the hardware on the SpinWheel.
  SpinWheel.begin();
}

int red = 0;
int green = 0;
int blue = 0;

void loop() {
  SpinWheel.readIMU();
  // If the rotation in the x direction is big enough,
  // turn the red LED of each big LED on.
  if (abs(SpinWheel.gx) > 1) {
    red = 255;
  }
  // If the rotation in the y direction is big enough,
  // turn the green LED of each big LED on.
  if (abs(SpinWheel.gy) > 1) {
    green = 255;
  }
  // If the rotation in the z direction is big enough,
  // turn the blue LED of each big LED on.
  if (abs(SpinWheel.gz) > 1)  {
    blue = 255;
  }
  // If the rotation in all directions is small enough,
  // turn the big LEDs off.
  if ((abs(SpinWheel.gx)+abs(SpinWheel.gy)+abs(SpinWheel.gz)) < 1) {
    red = 0;
    green = 0;
    blue = 0;
  }
  
  SpinWheel.setLargeLEDsUniform(red, green, blue);
  SpinWheel.setSmallLEDsUniform(red, green, blue);

  // Make the SpinWheel show the registered color.
  SpinWheel.drawFrame();
 }
  
