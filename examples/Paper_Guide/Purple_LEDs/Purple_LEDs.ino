#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // put your setup code here, to run once:
  SpinWheel.begin()
}

void loop() {
  // put your main code here, to run repeatedly:
  SpinWheel.setLargeLEDsUniform(255, 0, 255);
  SpinWheel.drawFrame();
}
