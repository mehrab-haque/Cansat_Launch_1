#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

int red_light_pin= 7;

float alt=0;
  
void setup() {
  pinMode(red_light_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("cansat initializing...");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully...");
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

     alt=bmp.readAltitude();

     String dataString="rocket_v1.0 :: altitude = "+String(alt)+" m";

     Serial.println(dataString);
    LoRa.beginPacket();
    LoRa.print(dataString);
    LoRa.endPacket();
    redLight();
    
    delay(500);
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  delay(95);
  digitalWrite(red_light_pin, LOW);
}
