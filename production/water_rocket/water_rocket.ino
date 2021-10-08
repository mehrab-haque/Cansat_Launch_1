#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP085.h>

#include <Servo.h>

Servo servo;  
int normalAngle = 0;    
int ejectedAngle = 90;

#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

int red_light_pin= 7;

float alt=0;


//ejection variables
float maxHeight=0;
float threshHoldDiff=10;
int ejectionConfirmation=4;
int ejectionCounter=0;

  
void setup() {
  pinMode(red_light_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("rocket initializing...");
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
  Serial.println("BMP180 initialization successfully...");
  servo.attach(6);
  servo.write(normalAngle);
  Serial.println("ejection servo initialization successfully...");
  Serial.println("cansat initialization completed...");
}
  
void loop() {

     alt=bmp.readAltitude();

     String dataString="rocket_v1.0 :: altitude = "+String(alt)+" m";

     

      if(alt>maxHeight)
        maxHeight=alt;
      if(maxHeight-alt>threshHoldDiff)
        ejectionCounter++;
      if(ejectionCounter>=ejectionConfirmation){
        eject();
        dataString="rocket_v1.0 :: ejection at altitude = "+String(alt);
      }
        

        Serial.println(dataString);
      LoRa.beginPacket();
      LoRa.print(dataString);
      LoRa.endPacket();
      redLight();
      
      delay(400);
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  delay(95);
  digitalWrite(red_light_pin, LOW);
}

void eject(){
  servo.write(ejectedAngle);
}
