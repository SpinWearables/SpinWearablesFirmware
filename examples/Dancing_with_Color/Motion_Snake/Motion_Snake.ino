/// # Dancing with Color: Step x, colorful snake that changes with
// motion
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // Initialize all of the hardware on the SpinWheel.
  SpinWheel.begin();
}

uint8_t angle; 

void loop() {
  SpinWheel.readIMU();

  // if there is sufficient rotation, have the snake rotate
  if (abs(SpinWheel.gx) > 1) { 
    angle = (millis()>>4)&0xff;    
  }

  // this is a function that we created to display a "snake"
  SpinWheel.setSmallLEDsPointer(angle, 500, 0, 255, 255);
    
 
  
  SpinWheel.setLargeLEDsUniform(100, 0, 0);

  // Make the SpinWheel show the registered color.
  SpinWheel.drawFrame();
}
  
