/// # Step Counter: Step 3, lighting up in response to motion
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  Serial.begin(115200);
  SpinWheel.begin();
}

void loop() {
  SpinWheel.readIMU();
  // The "sum of the squares" is a common way to measure total ammount of motion independent of direction.
  // Mathematicians call it "the norm of the vector describing the motion".
  float total_acceleration = sqrt(SpinWheel.ax*SpinWheel.ax+SpinWheel.ay*SpinWheel.ay+SpinWheel.az*SpinWheel.az);
  // This `total_acceleration` includes the effect of the gravitational field even at rest.
  // We want only the component of that measurement that is related to motion.
  float kinematic_acceleration = abs(total_acceleration - 1.0); // Kinematic is a fancy word for "related to moving".
  // Turn on the large LEDs when noticing motion.
  // The intensity for each color goes from 0 to 255 on the SpinWheel,
  // so we multiply the value of the kinematic_acceleration by a largish number,
  // to make the light more noticeable.
  int intensity = 20*kinematic_acceleration;
  // We mix equal red, green, and blue for white light.
  SpinWheel.setLargeLEDsUniform(intensity, intensity, intensity);
  // And we tell the SpinWheel to show the light pattern we registered on the previous line.
  SpinWheel.drawFrame();
  Serial.print(20*kinematic_acceleration);
  Serial.println();
}
