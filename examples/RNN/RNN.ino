#include "SpinWearables.h"
using namespace SpinWearables;

#include "net.h"

void pacer(long period_ms) {
  static long t = millis();
  while(millis()-t < period_ms){}
  t += period_ms;
}

void setup() {
  delay(100);
  Serial.begin(115200);
  SpinWheel.begin();
}

uint8_t rgb[3];

void loop() {
  size_t i;
  
  pacer(20);
  
  SpinWheel.readIMU();
  input[0] = SpinWheel.ax;
  input[1] = SpinWheel.ay;
  input[2] = SpinWheel.az;
  input[3] = SpinWheel.gx;
  input[4] = SpinWheel.gy;
  input[5] = SpinWheel.gz;
  size_t c = network();

  for (i=0;i<3;i++) {rgb[i]=0;}
  rgb[c] = 100;
  SpinWheel.setLargeLEDsUniform(rgb[0],rgb[1],rgb[2]);
  SpinWheel.drawLargeLEDFrame();
  
  for (i=0;i<6;i++) {
    Serial.print(input[i]);
    Serial.print('\t');
  }
  Serial.print(executionTimeMicros());
  Serial.print('\t');
  Serial.print(output[0]);
  Serial.print('\t');
  Serial.print(output[1]);
  Serial.print('\t');
  Serial.print(output[2]);
  Serial.print('\t');
  Serial.print(c);
  Serial.print('\t');
  Serial.println();
  Serial.flush();
}
