 #include "SpinWearables.h"
 using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

void loop() {
  SpinWheel.setLargeLED(0, 100, 100, 0);
  SpinWheel.setLargeLED(1, 100, 100, 100);
  SpinWheel.setLargeLED(2, 0, 100, 100);
  SpinWheel.setLargeLED(3, 100, 0, 100);
  SpinWheel.setLargeLED(4, 100, 0, 0);
  SpinWheel.setLargeLED(5, 0, 100, 0);
  SpinWheel.setLargeLED(6, 0, 0, 100);
  SpinWheel.setLargeLED(7, 100, 100, 100);

  SpinWheel.drawFrame();
}
