/// # Biology of Sight: Mixing Colors
/// Turning all of the large LEDs to a custom color.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  // Initialize all of the hardware on the SpinWheel.
  SpinWheel.begin();
  // Ask the SpinWheel to prepare all large LEDs to
  // show a particular color.
  SpinWheel.setLargeLEDsUniform(195, 0, 255);
  // Make the SpinWheel show the registered color.
  SpinWheel.drawFrame();
}

void loop() {
}
