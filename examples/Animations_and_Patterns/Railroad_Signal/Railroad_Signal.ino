/// # An Animation Resembling a Railroad Signal
///
/// In our [animations and patterns](https://spinwearables.com/animation/)
/// lesson we describe how an animation can be created by instructing
/// a computer to make a particular drawing dependent on a single number,
/// the current time.
///
/// This is a small example doing exactly that:
/// We read the current time, divide it in intervals,
/// and depending on the time since the start of the last interval,
/// we change the brightness of two LEDs, forcing them into opposing colors.
///
/// Some pieces of code are the same as in previous examples from
/// this series on coded animations, We do not comment them as extensively here,
/// but consult the [`Simple_Blink`](../Simple_Blink) example if you need a refresher.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

void loop() {
  int t = millis();
  int t_repeat = t % 2500;
// Here we use a function that turns the steadily increasing
// and then abruptly dropping `t_repeat`
// into a neater rising and falling pattern.
  int w = triangularWave(t_repeat/10);
// We also want a number that is the exact opposite of `w`.
// Something that is large and bright when `w` is small and
// that is also small when `w` is large.
  int w_opposite = 255 - w;
// Set LED number 0 to a red color with an intensity governed by `w`
  SpinWheel.setLargeLED(0, w, 0, 0);
// Set LED number 2 to a red color with an intensity governed by `w_opposite`
  SpinWheel.setLargeLED(2, 0, w_opposite, 0);
// Draw the image that was prepared in the previous lines.
  SpinWheel.drawFrame();
}
