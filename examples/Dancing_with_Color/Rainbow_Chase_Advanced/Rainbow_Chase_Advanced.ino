/// # A Few LEDs with continuously changing colors "chasing" each other
///
/// This is a sketch based on the Rainbow_Chase example from [animations and patterns](https://spinwearables.com/animation/).
///
/// In the Animations and Patterns Activity a "delay" or "offset" between the numbers governing the
/// colors of a given LED was introduced to make them look as if they are chasing each other. 
///
/// Our comments in this sketch focus on the differences from that Animations 
/// and Patterns Adventure. In particular, we focus on how we now use rotation
/// rather than time to update the animation.
//

#include "SpinWearables.h"
using namespace SpinWearables;

void setup() {
  SpinWheel.begin();
  Serial.begin(115200);
}

int r_cum = 0;

void loop() {
  SpinWheel.readIMU();

// Here we measure the rotation around the x-axis.  
  int r = (SpinWheel.gz);
  
// Then if the absolute value of this rotation is big
// enough, we add 1 to r_cum. In the original Rainbow_Chase
// example, the function millis() provided an  
// equivalent value for us. This bit of code ensures that 
// the color of the LEDs only cycles when the device is 
// moving. You can modify the threshold like in the other
// sketches for this lesson or change the number
// being added to r_cum to change how quickly the LEDs 
// change color.
  if (abs(r) > 50) {
    r_cum += 1;
  }

// We will have some fixed "delay" between the
// numbers controlling each LED's color.
// Change this number! What happens?
  int r_delay = 20;
// We will turn all of the LEDs on, but the
// color of each one of them will be governed by
// a slightly modified number.
  int r0 = r_cum % 250;
  int r1 = (r_cum+r_delay) % 250;
  int r2 = (r_cum+2*r_delay) % 250;
  int r3 = (r_cum+3*r_delay) % 250;
// Here we finally set those colors.
// Let's first turn on the large LEDs.
  SpinWheel.setLargeLED(0, colorWheel(r0));
  SpinWheel.setLargeLED(1, colorWheel(r1));
  SpinWheel.setLargeLED(2, colorWheel(r2));
  SpinWheel.setLargeLED(3, colorWheel(r3));
  SpinWheel.setLargeLED(4, colorWheel(r0));
  SpinWheel.setLargeLED(5, colorWheel(r1));
  SpinWheel.setLargeLED(6, colorWheel(r2));
  SpinWheel.setLargeLED(7, colorWheel(r3));
// Now we can turn on the small LEDs.
  SpinWheel.setSmallLED(0, colorWheel(r0));
  SpinWheel.setSmallLED(1, colorWheel(r0));
  SpinWheel.setSmallLED(2, colorWheel(r1));
  SpinWheel.setSmallLED(3, colorWheel(r1));
  SpinWheel.setSmallLED(4, colorWheel(r1));
  SpinWheel.setSmallLED(5, colorWheel(r2));
  SpinWheel.setSmallLED(6, colorWheel(r2));
  SpinWheel.setSmallLED(7, colorWheel(r2));
  SpinWheel.setSmallLED(8, colorWheel(r3));
  SpinWheel.setSmallLED(9, colorWheel(r3));
  SpinWheel.setSmallLED(10, colorWheel(r1));
  SpinWheel.setSmallLED(11, colorWheel(r0));
// Draw the image that was prepared in the previous lines.
  SpinWheel.drawFrame();
}
