/// # Dancing with Color: Color changes based on acceleration of the device.
///
/// In this example, we will step through the code used
/// to make the SpinWheel change color based on the acceleration in 
/// the x and y direction. For more information and previous examples,
/// refer to the [dancing companion page](https://spinwearables.com/dancing/).
//

// The include statement allows this code to use all the information and code in SpinWearables.h
#include "SpinWearables.h"
using namespace SpinWearables;

// The Setup function runs one time to make sure the SpinWheel is ready to execute the main code in the loop function
void setup() {
// This function makes sure that the LEDs are ready to be lit up
  SpinWheel.begin();
}

// The loop function contains the main code of this sketch, which runs repeatedly. This code makes the SpinWheel light up whenever it accelerates in the x or y direction. 
void loop() {
// ReadIMU first makes sure that the SpinWheel's sensor is working, and then stores the sensor's data.
  SpinWheel.readIMU();

// These lines initialize the variables ax and ay, acceleration in the x and y direction.
// These variables are set equal to the absolute value of the acceleration read by the sensor, times 100. This ensures that ax and ay are always postiive and are on the scale of 100s, so that we can use these numbers to set the LEDs of the SpinWheel. 
  float ax = abs(SpinWheel.ax)*100;
  float ay = abs(SpinWheel.ay)*100;
// The setLargeLEDsUniform function sets the color of the large LEDs on the SpinWheel. The number set in ax and ay will determine the exact color the SpinWheel light up. The color of the SpinWheel will change depending on how much it is accelerating. Try moving the SpinWheel around and see how the color changes.  
  SpinWheel.setLargeLEDsUniform(ax, ay, 0);
  SpinWheel.drawFrame();
}
