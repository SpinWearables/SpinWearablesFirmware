/// # Dancing with Color: Have the SpinWheel respond to both acceleration and rotation. 
///
/// Here we include one final code example. This example is designed
/// to be more complex than the previous examples and to inspire
/// future work. For more information and other examples, 
/// [click here](https://spinwearables.com/dancing/).
//

// These include statements should look familiar!
// As a reminder, they allow the program to access
// coding tools for the SpinWheel.
#include "SpinWearables.h"
using namespace SpinWearables;

// The setup function should also seem familiar.
// As a reminder, the `setup` function is run once when
// the SpinWheel turns on. Also, `SpinWheel.begin()`
// prepares the LED to accept new colors.
void setup() {
  SpinWheel.begin();
}

int offset = 0;
int colorChange;

uint8_t angle;

// Instructions in a loop function are repeated over and over again,
// in other words, "in a loop".
void loop() {
// The `readIMU` function checks if the sensor is ready
// and takes its current rotation data.
  SpinWheel.readIMU();
  // if rotation is fast, add a step to the offset
  if (abs(SpinWheel.gx) > 1) {
    offset = SpinWheel.gx*100; 
    Serial.println(offset);
  }

  // make the rainbow in the large LEDs
  for (int i=0; i<4; i++) {
    colorChange = offset+i*255/4;
    Serial.println(colorChange);
    SpinWheel.setLargeLED(i, colorWheel(colorChange));
    SpinWheel.setLargeLED(7-i, colorWheel(colorChange));
  }

  float total_acceleration = SpinWheel.ax + SpinWheel.ay + SpinWheel.az
  
  // make a snake in the small LEDs
  // if there is sufficient motion, have the snake move
  if (abs(total_acceleration) > 1) { 
    angle = (millis()>>4)&0xff;    
  }

  // this is a function that we created to display a "snake"
  SpinWheel.setSmallLEDsPointer(angle, 500, 0, 255, 255);

  SpinWheel.drawFrame();
}
