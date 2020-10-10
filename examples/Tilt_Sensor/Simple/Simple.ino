/// # A Simple Tilt Sensor
///
//

#include "SpinWearables.h"
using namespace SpinWearables; 

void setup() {
// Ensure all of the SpinWheel hardware is on.
  SpinWheel.begin();
}

void loop() {
// Read all sensor data.
  SpinWheel.readIMU();

// Scale the x and y measurement to a -255..255 range.
  int x = SpinWheel.ax*255;
  int y = SpinWheel.ay*255;

// Turn off all LEDs.
  SpinWheel.clearAllLEDs();

// If the tilt is in a given direction,
// turn on the corresponding LED.
  if (x>10) {
    SpinWheel.setLargeLED(5, x, x, x);
  }
  else if (x<-10) {
    SpinWheel.setLargeLED(7, -x, -x, -x);
  }

// Do the same for the Y orientation
  if (y>10) {
    SpinWheel.setLargeLED(4, x, x, x);
  }
  else if (y<-10) {
    SpinWheel.setLargeLED(6, -x, -x, -x);
  }

// Turn on the LEDs as commanded above.
  SpinWheel.drawFrame();
}
