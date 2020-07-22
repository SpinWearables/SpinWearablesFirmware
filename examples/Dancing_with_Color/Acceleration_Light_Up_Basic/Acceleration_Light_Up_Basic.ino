#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // put your setup code here, to run once:
  SpinWheel.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  SpinWheel.readIMU();
  float ax = abs(SpinWheel.ax)*100;
  float ay = abs(SpinWheel.ay)*100;
  SpinWheel.setLargeLEDsUniform(ax, ay, 0);
  SpinWheel.drawFrame();
}
