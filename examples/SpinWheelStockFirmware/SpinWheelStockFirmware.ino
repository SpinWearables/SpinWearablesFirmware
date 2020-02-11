/// # The Default SpinWheel firmware.
///
/// This includes a few preloaded animations that can be changed by pressing
/// the button.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  Serial.begin(115200);
  SpinWheel.begin();
  SpinWheel.addAnimationRoutine(tiltSensor2);
  SpinWheel.addAnimationRoutine(tiltSensor3);
  SpinWheel.addAnimationRoutine(largeRainbow);
  SpinWheel.addAnimationRoutine(smallWhiteRotating);
  SpinWheel.addAnimationRoutine(allBreathing);
  SpinWheel.addAnimationRoutine(tiltSensor);
  SpinWheel.addAnimationRoutine(compass);
  //SpinWheel.addAnimationRoutine(flashlight);
  bootAnimation();
  SpinWheel.largeLEDs.setBrightness(20);
}

void loop() {
  SpinWheel.readIMU();
  SpinWheel.runAnimationRoutine();
  SpinWheel.drawFrame();
  Serial.print(executionTime()); Serial.print('\t'); Serial.print(sqrt(SpinWheel.ax*SpinWheel.ax+SpinWheel.ay*SpinWheel.ay+SpinWheel.az*SpinWheel.az));
  Serial.println();
}
