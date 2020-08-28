#include "SpinWearables.h"
using namespace SpinWearables;
void setup() {
  SpinWheel.begin();
  // This line ensures that the communication hardware
  // on our device is ready to send messages.
  // The name "Serial" is such for historical reasons
  // (it is the name for this type of communication).
  Serial.begin(9600);// 9600 is the speed of the connection.
}

// variable to specify which LED to light up
int which_LED = 0; 

void loop() {
  // light up the specified LED
  SpinWheel.setLargeLED(which_LED, 255, 0, 0); 
  SpinWheel.drawFrame(); 
  // Send a message to the connected computer.
  // The message will be which LED is lit up.
  Serial.println(which_LED);
  // add in a delay to make the LEDs change at a reasonable speed
  delay(500);
  // Increase the value of the which_LED by 1.
  which_LED = which_LED + 1; 

}
