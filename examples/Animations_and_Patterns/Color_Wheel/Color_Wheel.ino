/// # A Color Wheel Animation
///
/// In our [animations and patterns](https://spinwearables.com/animation/)
/// lesson we describe how an animation can be created by instructing
/// a computer to make a particular drawing dependent on a single number,
/// the current time.
///
/// In [Simple_Blink](../Simple_Blink) and [Smoother_Blink](../Smoother_Blink)
/// we saw how to impose a brightness that smoothly changes over time.
///
/// Here we will see how to use the color wheel, i.e. the wheel of hues which
/// assigns different colors to every number from 0 to 255.
/// We will use this color wheel to impose a smoothly changing color
/// the same way we previously imposed a smoothly changing brightness. 
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
// We prepare the number `s` which will be turned into a color by
// the colorWheel function.
  int s = t_repeating/10;
// We use the result of `colorWheel(s)` as input for the
// `setLargeLEDsUniform` function.
  SpinWheel.setLargeLEDsUniform(colorWheel(s));
  SpinWheel.drawFrame();
}
