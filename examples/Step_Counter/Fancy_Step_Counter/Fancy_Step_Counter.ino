/// # Step Counter, Complete
/// We use a slightly fancier light-up pattern, where we rapidly brighten the
/// LEDs in the presence of motion and only slowly dim them to darkness when at
/// rest.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  Serial.begin(115200);
  SpinWheel.begin();
}

float total_motion = 0;
float threshold = 0.1;
float conversion_factor = 0.3;
float filtered_intensity = 0;

void loop() {
  SpinWheel.readIMU();
  float total_acceleration = sqrt(SpinWheel.ax*SpinWheel.ax+SpinWheel.ay*SpinWheel.ay+SpinWheel.az*SpinWheel.az);
  float kinematic_acceleration = abs(total_acceleration - 1.0);
  filtered_intensity = faston_slowoff(filtered_intensity, 20*kinematic_acceleration, 0.1);
  int intensity = filtered_intensity;
  SpinWheel.setLargeLEDsUniform(intensity, intensity/2, intensity);
  if (kinematic_acceleration>threshold) {
    total_motion = total_motion+conversion_factor*kinematic_acceleration;
  }
  SpinWheel.setSmallLEDs(0,min(total_motion, 12),255,255,255);
  SpinWheel.drawFrame();
  //Serial.println(kinematic_acceleration);
}
