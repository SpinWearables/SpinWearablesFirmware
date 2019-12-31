#include "Adafruit_NeoPixel.h"
#include "ICM_20948.h"
#include <math.h>

namespace SpinWearables {

#define ONETWELFTH 21
#define MAXROUTINES 10
#define SMALLLEDTIMEDIV 1
#define FILTER_DIV 8
#define FILTER_A 64
#define FILTER_B ((1<<FILTER_DIV) - FILTER_A)

// Profiling functions

long executionTime() {
  static long t = millis();
  long r = millis()-t;
  t = millis();
  return r;
}

// Drawing convenience functions

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
  return (((uint32_t)r)<<16)+(((uint32_t)g)<<8)+b;  
}

uint32_t colorWheel(uint8_t wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
    return color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  wheelPos -= 170;
  return color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

uint8_t triangularWave(uint8_t x) {
  if (x>0x7f) {
    return (0xff-x)<<1;
  } else {
    return x<<1;
  }
}

uint8_t parabolaWave(uint8_t x) {
  uint8_t xm = x;
  if (xm>0x7f) {xm = 0xff-xm;}
  return (xm*xm)>>7;
}

// Temporal filter functions

float faston_slowoff(float filtered_intensity, float current_intensity, float decay) {
  if (current_intensity > filtered_intensity) {
      return current_intensity;
  } else {
      return decay*current_intensity + (1-decay)*filtered_intensity;
  }
}

// Forward declaration for the interrupt dispatch (necessary as attachInterrupt does not provide for user data, so we are using a global function).
void cycleAnimationRoutine();

class SpinWheelClass {
  public:
    SpinWheelClass() {
      largeLEDs = Adafruit_NeoPixel(8, 15, NEO_GRB + NEO_KHZ800); // XXX HARDWARE DETAIL: 8 LEDs on pin d15.
    };

    void begin(bool button=true) {
      PORTB &= B00000011;
      PORTD |= B11111100;
      DDRB |= B11111100;
      DDRD |= B11111100;
      largeLEDs.begin(); 
      largeLEDs.show();
      Wire.begin();
      Wire.setClock(400000);
      IMU.begin(Wire, 1); // XXX HARDWARE DETAIL; AD0 is pulled.
      // TODO check that the IMU works.
      if (button) {
        digitalWrite(7, INPUT_PULLUP); // XXX HARDWARE DETAIL: Pin D7 is connected to the button.
        attachInterrupt(digitalPinToInterrupt(7), cycleAnimationRoutine, FALLING);
      }
    }

    uint8_t smallLEDs[36];
    Adafruit_NeoPixel largeLEDs;
    
    ICM_20948_I2C IMU;
    float ax, ay, az, gx, gy, gz, mx, my, mz;
    int8_t ax_int, ay_int, az_int, gx_int, gy_int, gz_int, mx_int, my_int, mz_int;
    int32_t taxsmooth, taysmooth, tazsmooth, tgxsmooth, tgysmooth, tgzsmooth, tmxsmooth, tmysmooth, tmzsmooth;

    void (*animationroutines[MAXROUTINES]) (void);
    size_t current_animation = 0;
    size_t registered_animations = 0;
    
    void drawFrame() {
      drawSmallLEDFrame();
      drawLargeLEDFrame();
    }

    void drawFrame(unsigned long timeout) {
      unsigned long t = millis();
      drawLargeLEDFrame();
      while(millis()-t<timeout) {drawSmallLEDFrame();}
    }

    void drawSmallLEDFrame() { // XXX HARDWARE DETAIL: B2-B7 and D2-D7 make up the small LEDs grid.
      for(int frame=0; frame<2<<SMALLLEDTIMEDIV; frame++) { // XXX: 2 repetitions lead to drawSmallLEDFrame taking 0.021 seconds.
        for(int i=0; i<6; i++) {
          PORTB &= B00000011;
          PORTB |= B00000100 << i;
          for(int j=0; j<6; j++) {
            uint8_t d = smallLEDs[i*6+j];
            if (d) {
              PORTD ^= B00000100 << j;
              delayMicroseconds(d>>SMALLLEDTIMEDIV);
              PORTD |= B11111100;
            }
            delayMicroseconds((255-d)>>SMALLLEDTIMEDIV);
          }
        }
      }
    }

    void drawLargeLEDFrame() {
      largeLEDs.show();  
    }

    void readIMU() {
      if( IMU.dataReady() ){
        IMU.getAGMT();
        taxsmooth = (((int32_t)IMU.agmt.acc.axes.x)*FILTER_A + taxsmooth*FILTER_B)>>FILTER_DIV;
        taysmooth = (((int32_t)IMU.agmt.acc.axes.y)*FILTER_A + taysmooth*FILTER_B)>>FILTER_DIV;
        tazsmooth = (((int32_t)IMU.agmt.acc.axes.z)*FILTER_A + tazsmooth*FILTER_B)>>FILTER_DIV;
        tgxsmooth = (((int32_t)IMU.agmt.gyr.axes.x)*FILTER_A + tgxsmooth*FILTER_B)>>FILTER_DIV;
        tgysmooth = (((int32_t)IMU.agmt.gyr.axes.y)*FILTER_A + tgysmooth*FILTER_B)>>FILTER_DIV;
        tgzsmooth = (((int32_t)IMU.agmt.gyr.axes.z)*FILTER_A + tgzsmooth*FILTER_B)>>FILTER_DIV;
        tmxsmooth = (((int32_t)IMU.agmt.mag.axes.x)*FILTER_A + tmxsmooth*FILTER_B)>>FILTER_DIV;
        tmysmooth = (((int32_t)IMU.agmt.mag.axes.y)*FILTER_A + tmysmooth*FILTER_B)>>FILTER_DIV;
        tmzsmooth = (((int32_t)IMU.agmt.mag.axes.z)*FILTER_A + tmzsmooth*FILTER_B)>>FILTER_DIV;
        ax_int = taxsmooth>>8;
        ay_int = taysmooth>>8;
        az_int = tazsmooth>>8;
        gx_int = tgxsmooth>>8;
        gy_int = -tgysmooth>>8;
        gz_int = -tgzsmooth>>8;
        mx_int = tmxsmooth>>3;
        my_int = -tmysmooth>>3;
        mz_int = -tmzsmooth>>3;
        ax = taxsmooth / 16384.;
        ay = taysmooth / 16384.;
        az = tazsmooth / 16384.;
        gx = tgxsmooth / 16384.;
        gy = tgysmooth / 16384.;
        gz = tgzsmooth / 16384.;
        mx = tmxsmooth / 16384.;
        my = tmysmooth / 16384.;
        mz = tmzsmooth / 16384.;
	
      }
    }

    void runAnimationRoutine() {
      if (registered_animations && current_animation < registered_animations && animationroutines[current_animation]!=0) {
        animationroutines[current_animation]();
      }
    }

    void addAnimationRoutine(void (*routine) (void)) {
      if (registered_animations<MAXROUTINES) {
        animationroutines[registered_animations] = routine;
        registered_animations++;
      }
    }

    void setSmallLEDsRainbow(uint8_t angle) {
      for (int i=0; i<12; i++) {
        setSmallLED(i, colorWheel(angle+i*ONETWELFTH));
      }
    }
    
    void setSmallLED(int i, uint8_t r, uint8_t g, uint8_t b) {
      smallLEDs[i*3] = r;
      smallLEDs[i*3+1] = g;
      smallLEDs[i*3+2] = b;  
    }
    
    void setSmallLED(int i, uint32_t rgb) {
      smallLEDs[i*3] = rgb>>16;
      smallLEDs[i*3+1] = rgb>>8;
      smallLEDs[i*3+2] = rgb;  
    }

    void setSmallLEDs(int i, int j, uint8_t r, uint8_t g, uint8_t b) {
      for (int ii=max(0,i); ii<min(12,j); ii++) setSmallLED(ii,r,g,b);
    }

    void setSmallLEDs(int i, int j, uint32_t rgb) {
      for (int ii=max(0,i); ii<min(12,j); ii++) setSmallLED(ii,rgb);
    }
    
    void setSmallLEDsUniform(uint8_t r, uint8_t g, uint8_t b) {
      for (int i=0; i<12; i++) {
        smallLEDs[i*3] = r;
        smallLEDs[i*3+1] = g;
        smallLEDs[i*3+2] = b;  
      }
    }
    
    void setSmallLEDsUniform(uint32_t rgb) {
      for (int i=0; i<12; i++) {
        smallLEDs[i*3] = rgb>>16;
        smallLEDs[i*3+1] = rgb>>8;
        smallLEDs[i*3+2] = rgb;
      }
    }

    void setLargeLED(int i, uint8_t r, uint8_t g, uint8_t b) {
      largeLEDs.setPixelColor(i,r,g,b);
    }
    
    void setLargeLED(int i, uint32_t rgb) {
      largeLEDs.setPixelColor(i,rgb);
    }
    
    void setLargeLEDsUniform(uint8_t r, uint8_t g, uint8_t b) {
      largeLEDs.fill(color(r,g,b), 0, 8);
    }
    
    void setLargeLEDsUniform(uint32_t rgb) {
      largeLEDs.fill(rgb, 0, 8);
    }

    void clearSmallLEDs() {
      setSmallLEDsUniform(0);  
    }

    void clearLargeLEDs() {
      largeLEDs.fill(0, 0, 8);
    }

    void clearAllLEDs() {
      setSmallLEDsUniform(0);  
      setLargeLEDsUniform(0);      
    }
        
    void setSmallLEDsPointer(uint8_t angle, int64_t decay, uint8_t r, uint8_t g, uint8_t b) {
      for (int i=0; i<12; i++) {
        uint8_t rel = angle-i*ONETWELFTH;
        if (rel>=128) rel = 255-rel;
        uint32_t arel = max(255-rel*decay*2l/255,0);
        uint8_t tr = r*arel/255;
        uint8_t tg = g*arel/255;
        uint8_t tb = b*arel/255;
        setSmallLED(i,tr,tg,tb);
      }
    }
    
    void setSmallLEDsPointer(uint8_t angle, int64_t decay, uint32_t rgb) {
      setSmallLEDsPointer(angle, decay, rgb>>16, rgb>>8, rgb);
    }
    
    void setSmallLEDsProgress(uint8_t angle, uint8_t r, uint8_t g, uint8_t b) {
      int i;
      for (i=0; i<angle/ONETWELFTH; i++) {
        setSmallLED(i, r, g, b);
      }
      if (i==12) return;
      uint32_t br = angle%ONETWELFTH;
      setSmallLED(i, br*r/ONETWELFTH, br*g/ONETWELFTH, br*b/ONETWELFTH);
    }

    void setSmallLEDsProgress(uint8_t angle, uint32_t rgb) {
      setSmallLEDsProgress(angle, rgb>>16, rgb>>8, rgb);
    }
};

SpinWheelClass SpinWheel;

void cycleAnimationRoutine() { // called from interrupt
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200){
    SpinWheel.clearAllLEDs();
    SpinWheel.current_animation++;
    SpinWheel.current_animation %= SpinWheel.registered_animations;
  }
  last_interrupt_time = interrupt_time;
}

// Preloaded animations

void bootAnimation() {
  for (uint8_t i=0; i<252; i+=4) {
    SpinWheel.setSmallLEDsUniform(i,i,i);
    SpinWheel.drawFrame();
  }
  for (uint8_t i=252; i>0; i-=4) {
    SpinWheel.setSmallLEDsUniform(i,i,i);
    SpinWheel.drawFrame();
  }
  SpinWheel.clearSmallLEDs();
  for (uint8_t i=0; i<32; i++) {
    SpinWheel.setLargeLEDsUniform(i,i,i);
    SpinWheel.drawFrame();
  }
  for (uint8_t i=32; i>0; i--) {
    SpinWheel.setLargeLEDsUniform(i,i,i);
    SpinWheel.drawFrame();
  }
  SpinWheel.clearLargeLEDs();  
  SpinWheel.drawFrame();
}

void smallWhiteRotating() {
  uint8_t angle = (millis()>>4)&0xff;
  SpinWheel.setSmallLEDsPointer(angle, 500, 0xffffff);
}

void allBreathing() {
  uint8_t t = (millis()>>4)&0xff;
  uint8_t b1 = parabolaWave(t);
  uint8_t b2 = parabolaWave(t+20);
  uint8_t b3 = parabolaWave(t+70);
  uint8_t b4 = parabolaWave(t+90);
  for (int i=0; i<4; i++) {
    SpinWheel.largeLEDs.setPixelColor(i,b1,0,b1);
  }
  for (int i=4; i<8; i++) {
    SpinWheel.largeLEDs.setPixelColor(i,b2,0,b2);
  }
  for (int i=0; i<12; i++) {
    if (i%2==1) {
      SpinWheel.setSmallLED(i,b3,0,b3);
    } else {
      SpinWheel.setSmallLED(i,b4,0,b4);
    }
  }
}

void tiltSensor() {
  int8_t x = SpinWheel.ax_int;  
  int8_t y = SpinWheel.ay_int;
  SpinWheel.clearLargeLEDs();
  if (x>0) SpinWheel.largeLEDs.setPixelColor(7,x,0,x);
  else SpinWheel.largeLEDs.setPixelColor(5,-x,0,-x);
  if (y>0) SpinWheel.largeLEDs.setPixelColor(4,y,0,y);
  else SpinWheel.largeLEDs.setPixelColor(6,-y,0,-y);
}

void compass() {
  int8_t x = SpinWheel.ax_int;  
  int8_t y = SpinWheel.ay_int;
  SpinWheel.clearLargeLEDs();
  if (x>10) SpinWheel.largeLEDs.setPixelColor(7,x-8,0,0);
  else if (x<-10) SpinWheel.largeLEDs.setPixelColor(5,-x+8,0,0);
  else {
    SpinWheel.largeLEDs.setPixelColor(1,0,0,32-3*abs(x));
    SpinWheel.largeLEDs.setPixelColor(3,0,0,32-3*abs(x));
  }
  if (y>10) SpinWheel.largeLEDs.setPixelColor(4,y-8,0,0);
  else if (y<-10) SpinWheel.largeLEDs.setPixelColor(6,-y+8,0,0);
  else {
    SpinWheel.largeLEDs.setPixelColor(0,0,0,32-3*abs(y));
    SpinWheel.largeLEDs.setPixelColor(2,0,0,32-3*abs(y));
  }
  uint8_t angle = (atan2(SpinWheel.my_int, SpinWheel.mx_int)+3.1415/2)/2/3.1415*255;
  SpinWheel.setSmallLEDsPointer(angle, 500, 0xffffff);
}

void tiltSensor2() {
  int8_t x = SpinWheel.ax_int;  
  int8_t y = SpinWheel.ay_int;
  SpinWheel.setLargeLEDsUniform(0xffffff);
  if (x>10) {
    SpinWheel.largeLEDs.setPixelColor(7,x-8,0,x-8);
    SpinWheel.largeLEDs.setPixelColor(3,x-8,0,x-8);
  }
  else if (x<-10) {
    SpinWheel.largeLEDs.setPixelColor(5,-x+8,0,-x+8);
    SpinWheel.largeLEDs.setPixelColor(1,-x+8,0,-x+8);
  }
  if (y>10) {
    SpinWheel.largeLEDs.setPixelColor(4,y-8,0,y-8);
    SpinWheel.largeLEDs.setPixelColor(0,y-8,0,y-8);
  }
  else if (y<-10) {
    SpinWheel.largeLEDs.setPixelColor(6,-y+8,0,-y+8);
    SpinWheel.largeLEDs.setPixelColor(2,-y+8,0,-y+8);
  }
  SpinWheel.setSmallLEDsUniform(0xffffff);
}

void flashlight() {
  SpinWheel.setSmallLEDsUniform(0xffffff);  
  SpinWheel.largeLEDs.fill(0xffffff, 0, 8);
}

void largeRainbow() {
  long int angle = millis()/20;
  SpinWheel.setSmallLEDsUniform(0xffffff);
  for (int i=0; i<4; i++) {
    SpinWheel.setLargeLED(i, colorWheel(angle+i*255/4));
    SpinWheel.setLargeLED(7-i, colorWheel(angle+i*255/4));
  }
}

} // end namespace SpinWearables

