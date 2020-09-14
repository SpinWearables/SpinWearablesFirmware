#include "SpinWearables.h"
using namespace SpinWearables; 
void setup() {
  SpinWheel.begin();
  // The next line ensures that the communication hardware
  // on our device is ready to send messages.
  // The name "Serial" is such for historical reasons
  // (it is the name for this type of communication).
  Serial.begin(9600);// The 9600 is the speed of the communication.
}

void loop() {
 // This line gets the information from the SpinWheel's 
 // motion sensor.
 SpinWheel.readIMU();
 // Send a message to the connected computer. 
 // The message will just be the value of the SpinWheel's
 // rotation around the x-axis.
 Serial.println(SpinWheel.gx);
 // Wait for 20 milliseconds (i.e. repeat 50 times a second)
 // before you start the loop function again.
 // This value might be different in some of our paper educational materials.
 // Changing it simply makes the sensor more or less responsive.
 delay(20); 
}
