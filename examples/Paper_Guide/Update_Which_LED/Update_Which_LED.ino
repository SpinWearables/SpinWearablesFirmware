#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

// variable to specify which LED to light up
int which_LED = 0; 

void loop() {
  // light up the specified LED
  SpinWheel.setLargeLED(which_LED, 255, 0, 0); 
  SpinWheel.drawFrame(); 
  // add in a delay to make the LEDs change at a reasonable speed
  delay(500);
  // Increase the value of which_LED by 1.
  which_LED = which_LED + 1; 
}
