#include "SpinWearables.h"
using namespace SpinWearables;
void setup() {
  SpinWheel.begin();
}

void loop() {
  // create a variable called which_LED
  int which_LED = 1; 
  // light up the Large LED that corresponds
  // to which_LED
  SpinWheel.setLargeLED(which_LED, 255, 0, 0); 
  SpinWheel.drawFrame(); 
}
