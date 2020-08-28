 #include "SpinWearables.h"
 using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

void loop() {
  SpinWheel.setLargeLED(0, 50, 50, 0);
  SpinWheel.setLargeLED(1, 50, 50, 50);
  SpinWheel.setLargeLED(2, 0, 50, 50);
  SpinWheel.setLargeLED(3, 50, 0, 50);
  SpinWheel.setLargeLED(4, 50, 0, 0);
  SpinWheel.setLargeLED(5, 0, 50, 0);
  SpinWheel.setLargeLED(6, 0, 0, 50);
  SpinWheel.setLargeLED(7, 50, 50, 50);

  SpinWheel.drawFrame();
}
