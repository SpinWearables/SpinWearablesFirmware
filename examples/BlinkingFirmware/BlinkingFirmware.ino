/// # A Simple Example Sketch for the SpinWheel
///
/// Part of the [Quick Start](https://spinwearables.com/quickstart/)
//

// These few lines instruct the software to preload
// all the extra tools we have created specifically
// for the SpinWheel.
#include "SpinWearables.h"
using namespace SpinWearables;

// The `setup` function is executed only once,
// when the SpinWheel turns on. As the name suggests,
// it serves as a place where any initial functionality
// can be set up. We simply instruct the SpinWheel
// to begin accepting commands.
void setup() {
  SpinWheel.begin();
}

// The `loop` function is executed repeatedly,
// as fast as possible, in a loop.
// It serves as the main "logic" that drives
// the behavior of the SpinWheel.
void loop() {
// Typically, the loop function will first
// measure the current time and motion readings,
// and then create colorful pattern depending on
// the measurement values.
  int t = millis();
  int t_repeating = t % 2500;
  int b = triangularWave(t_repeating / 10);
// The colors of the LEDs are set with commands
// like this one.
  SpinWheel.setLargeLEDsUniform(b, 0, b);
// And typically the `loop` function ends with
// a call to the `drawFrame` function, which
// ensures that all LEDs are on with the previously
// set color.
  SpinWheel.drawFrame();
}
