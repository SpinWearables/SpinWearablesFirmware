#include "SpinWearables.h"
using namespace SpinWearables; 

void setup() {
  SpinWheel.begin();
}

void loop() {
  SpinWheel.setLargeLED(0,255,0,0);
  SpinWheel.drawFrame(); 
}
