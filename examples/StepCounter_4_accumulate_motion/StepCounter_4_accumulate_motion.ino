/// # Step Counter: Step 4, accumulate motion measurements
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  Serial.begin(115200);
  SpinWheel.begin();
}

float total_motion = 0;
float threshold = 0.1;
float conversion_factor = 0.01;

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
  // Accumulate all of the motion readings over time in a single number.
  // To avoid false readings, perform the accumulation only if the motion was sufficiently strong.
  if (kinematic_acceleration>threshold) {
    total_motion = total_motion+conversion_factor*kinematic_acceleration;
  }
  // Display how much you have moved, by turning on the corresponding number of small LEDs.
  SpinWheel.setSmallLEDs(0,min(total_motion, 12),255,255,255);
  // And we tell the SpinWheel to show the light pattern we registered on the previous line.
  SpinWheel.drawFrame();
  Serial.print(total_motion);
  Serial.println();
}
