#include "SpinWearables.h"
using namespace SpinWearables;
void setup() {
  SpinWheel.begin();
}

void loop() {
  int which_LED = 1; 
  SpinWheel.setLargeLED(which_LED, 255, 0, 0); 
  SpinWheel.drawFrame(); 
}
