/// # Dancing with Color: Step x, have the color wheel change only 
// if there is rotation
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

int offset = 0;
int colorChange;

uint8_t angle;

void loop() {
  SpinWheel.readIMU();
  // if rotation is fast, add a step to the offset
  if (abs(SpinWheel.gx) > 1) {
    offset = SpinWheel.gx*100; 
    Serial.println(offset);
  }

  // make the rainbow in the large LEDs
  for (int i=0; i<4; i++) {
    colorChange = offset+i*255/4;
    Serial.println(colorChange);
    SpinWheel.setLargeLED(i, colorWheel(colorChange));
    SpinWheel.setLargeLED(7-i, colorWheel(colorChange));
  }


  // make a snake in the small LEDs
  // if there is sufficient rotation, have the snake rotate
  if (abs(SpinWheel.gx) > 1) { 
    angle = (millis()>>4)&0xff;    
  }

  // this is a function that we created to display a "snake"
  SpinWheel.setSmallLEDsPointer(angle, 500, 0, 255, 255);

  SpinWheel.drawFrame();
}
