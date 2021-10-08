#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;

float alt=0;
float temp=0;
float pressure=0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("cansat initializing...");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully...");
  if (!bmp.begin()) {
    Serial.println("BMP180 initialization failed");
    while (1) {}
  }
  Serial.println("BMP180 initialization successfully...");
  Serial.println("cansat initialization completed...");
  
}
void loop() 
{
  temp=bmp.readTemperature();
  alt=bmp.readAltitude();
  pressure=bmp.readPressure();
  String dataString="cansat_v1.0 :: temp = "+String(temp)+" *C, pressure = "+String(pressure)+" Pa, altitude = "+String(alt)+" m";
  Serial.println(dataString);
  LoRa.beginPacket();
  LoRa.print(dataString);
  LoRa.endPacket();
  delay(500);
}
