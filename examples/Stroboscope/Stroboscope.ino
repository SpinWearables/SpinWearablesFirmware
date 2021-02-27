/// # A Stroboscope
/// As seen in the SpinWheel [stroboscope adventure](https://spinwearables.com/stroboscope/)
//

#include "SpinWearables.h"
using namespace SpinWearables;

// First we would like to ensure the brightness
// is set to maximum, as we are not going to use
// the LEDs for aesthetics,
// but rather as a source of illumination.
void setup() {
  SpinWheel.begin();
  SpinWheel.setBrightness(255);
}

// We will set the default period to
// 10 milliseconds and let it vary
// from 8 milliseconds to 12 milliseconds.
long default_delay_time = 10000;
long max_correction = 2000;

// And now we have the main body of the program,
// which will turn the light on and then off rapidly.
void loop() {

// We first read the tilt of the device and use it
// to modify the default period.
  SpinWheel.readIMU();
  long delaytime = default_delay_time + SpinWheel.ax * max_correction;

// Set the lights on.
  SpinWheel.setLargeLEDsUniform(255, 255, 255);
  SpinWheel.drawLargeLEDFrame();

// Wait only a small fraction of the total period (3% in this case).
  delayMicroseconds(0.03*delaytime);

// Then turn the lights off and wait for the rest of the time.
  SpinWheel.setLargeLEDsUniform(0, 0, 0);
  SpinWheel.drawLargeLEDFrame();
  delayMicroseconds(0.97*delaytime);
}

// Notice we used `drawLargeLEDFrame()` instead of `drawFrame()`.
// We did so because `drawFrame` also sets the small LEDs,
// which used a much slower persistence-of-vision pattern
// and can not work at more than 50 frames per second.
