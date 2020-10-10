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

// Turn all large LEDs white.
  SpinWheel.setLargeLEDsUniform(0xffffff);

// If the tilt is in a given direction,
// turn on the corresponding LED purple.
  if (x>10) {
    SpinWheel.setLargeLED(7, x, 0, x);
    SpinWheel.setLargeLED(3, x, 0, x);
  }
  else if (x<-10) {
    SpinWheel.setLargeLED(5, -x, 0, -x);
    SpinWheel.setLargeLED(1, -x, 0, -x);
  }

// Do the same for the Y orientation
  if (y>10) {
    SpinWheel.setLargeLED(6, x, 0, x);
    SpinWheel.setLargeLED(2, x, 0, x);
  }
  else if (y<-10) {
    SpinWheel.setLargeLED(4, -x, 0, -x);
    SpinWheel.setLargeLED(0, -x, 0, -x);
  }

// Use the `setSmallLEDsPointer` to turn on only the small LEDs
// which are at the top. This requires some tricky inverse
// trigonometry, where we use the arctan function to turn the
// `ay` and `ax` measurements into an angle. Then we rescale that angle
// to fit the 0..255 range used by `setSmallLEDsPointer`.
  uint8_t angle = (-atan2(SpinWheel.ay, SpinWheel.ax)+3.1415/2)/2/3.1415*255;
  SpinWheel.setSmallLEDsPointer(angle, 0xffffff);

// Turn on the LEDs as commanded above.
  SpinWheel.drawFrame();
}
