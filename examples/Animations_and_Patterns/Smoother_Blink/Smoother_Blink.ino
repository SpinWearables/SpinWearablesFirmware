/// # A Smoother Blink Animation Using a Timer
///
/// In our [animations and patterns](https://spinwearables.com/animation/)
/// lesson we describe how an animation can be created by instructing
/// a computer to make a particular drawing dependent on a single number,
/// the current time.
///
/// The first example we considered, [Simple_Blink](../Simple_Blink),
/// has somewhat abrupt change from bright to dark. Here we use the
/// `triangularWave` function to make the pulsing pattern more pleasant and
/// less abrupt.
///
/// Some pieces of code are the same as in previous examples from
/// this series on coded animations, We do not comment them as extensively here,
/// but consult the `Simple_Blink` example if you need a refresher.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
}

void loop() {
  int t = millis();
  int t_repeating = t % 2500;
// The triangularWave function has a period of 256
// and provides for a smooth ramp-up and ramp-down.
  int b = triangularWave(t_repeating / 10);
// The next function takes three arguments:
// The red, green, and blue components of the color we desire.
// We are mixing only red and blue, setting green to zero.
  SpinWheel.setLargeLEDsUniform(b, 0, b);
  SpinWheel.drawFrame();
}
