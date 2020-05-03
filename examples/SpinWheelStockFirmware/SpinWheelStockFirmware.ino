/// # The Default SpinWheel firmware.
///
/// This includes a few preloaded animations that can be changed by pressing
/// the button.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
  SpinWheel.largeLEDs.setBrightness(20);
  bootAnimation();
  SpinWheel.addAnimationRoutine(largeRainbow);
  SpinWheel.addAnimationRoutine(smallWhiteRotating);
  SpinWheel.addAnimationRoutine(allBreathing);
  SpinWheel.addAnimationRoutine(tiltSensor3);
  SpinWheel.addAnimationRoutine(tealLight);
}

void loop() {
  SpinWheel.readIMU();
  SpinWheel.runAnimationRoutine();
  SpinWheel.drawFrame();
}
