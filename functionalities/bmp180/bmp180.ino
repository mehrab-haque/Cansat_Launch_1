#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

int n=10;
  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}
  
void loop() {

//    float total=0;
//
//     for(int i=0;i<n;i++){
//      total+=bmp.readAltitude();
//     }

     Serial.println(bmp.readAltitude());
    
    
    delay(500);
}
