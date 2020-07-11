#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // Initialize all of the hardware on the SpinWheel.
  SpinWheel.begin();
}

int pos_spin = 0;
int neg_spin = 0;

void loop() {
  SpinWheel.readIMU();
  // If the x rotation (gx) is big enough, then 
  // change the color of the big LEDs based on the
  // direction of the spin
  if (abs(SpinWheel.gx) > 1) {
    pos_spin = 255;
    neg_spin = 0;
  }
  else if (SpinWheel.gx < -1) {
    neg_spin = 255;
    pos_spin = 0;
  }
  else {
    pos_spin = 0;
    neg_spin = 0;
  }
  // If gz is positive, set the big LEDs to light up green
  // If gz is negative, set the big LEDs to light up blue
  SpinWheel.setLargeLEDsUniform(0, pos_spin, neg_spin);
  // Make the SpinWheel show the registered color.
  SpinWheel.drawFrame();
 }
