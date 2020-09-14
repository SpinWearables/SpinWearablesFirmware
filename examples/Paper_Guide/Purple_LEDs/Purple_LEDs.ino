#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

void loop() {
  SpinWheel.setLargeLEDsUniform(255, 0, 255);
  SpinWheel.drawFrame();
}
