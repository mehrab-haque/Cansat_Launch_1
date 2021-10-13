#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;

float alt=0;
float temp=0;
float pressure=0;

int red_light_pin= 6;
int green_light_pin = 7;

void setup() 
{
  greenLight();
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  
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
  String dataString="["+String(temp)+","+String(pressure)+","+String(alt)+"]";
  Serial.println(dataString);
  LoRa.beginPacket();
  LoRa.print(dataString);
  LoRa.endPacket();
  redLight();
  delay(250);
}

void greenLight(){
  digitalWrite(red_light_pin, LOW);
  digitalWrite(green_light_pin, HIGH);
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  digitalWrite(green_light_pin, LOW);
  delay(95);
  greenLight();
}
