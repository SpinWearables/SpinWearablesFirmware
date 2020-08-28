#include "SpinWearables.h"
using namespace SpinWearables;
void setup() {
  SpinWheel.begin();
  Serial.begin(9600);
}

int which_LED = 0; 

void loop() {
  SpinWheel.setLargeLED(which_LED, 255, 0, 0); 
  SpinWheel.drawFrame(); 
  Serial.println(which_LED);
  delay(500);
  which_LED = which_LED + 1; 

}
