/// # Step Counter: Step 2, detect only acceleration due to motion
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
  Serial.print(kinematic_acceleration);
  Serial.println();
}
