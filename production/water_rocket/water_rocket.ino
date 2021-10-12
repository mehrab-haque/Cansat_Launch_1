#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP085.h>

#include <Servo.h>

Servo servo1;  
int normalAngle1 = 0;    
int ejectedAngle1 = 90;

Servo servo2;  
int normalAngle2 = 0;    
int ejectedAngle2 = 90;

#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

int red_light_pin= 7;

float alt=0;


//ejection variables
//float maxHeight=0;
//float threshHoldDiff=10;
//int ejectionConfirmation=4;
//int ejectionCounter=0;
bool r=false;
  
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
  LoRa.onReceive(onReceive);
  LoRa.receive();
  //LoRa.onTxDone(onTxDone);
  Serial.println("LoRa listening...");
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  Serial.println("BMP180 initialization successfully...");
  servo1.attach(5);
  servo2.attach(6);
  lock();
  Serial.println("ejection servo initialization successfully...");
  Serial.println("cansat initialization completed...");
}
  
void loop() {

//     alt=bmp.readAltitude();
//
//     String dataString="rocket_v1.0 :: altitude = "+String(alt)+" m";

     

//      if(alt>maxHeight)
//        maxHeight=alt;
//      if(maxHeight-alt>threshHoldDiff)
//        ejectionCounter++;
//      if(ejectionCounter>=ejectionConfirmation){
//        eject();
//        dataString="rocket_v1.0 :: ejection at altitude = "+String(alt);
//      }
        

//        Serial.println(dataString);
//      LoRa.beginPacket();
//      LoRa.print(dataString);
//      LoRa.endPacket();
//      redLight();
//      
//      delay(400);

        if(r){
          redLight();
          r=false;
        }
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;         
  String incoming = "";

 

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  if(incoming[0]=='g' and incoming[1]=='l'){
    r=true;
    lock();
    Serial.println(incoming);
  }
  if(incoming[0]=='g' and incoming[1]=='e'){
    r=true;
    eject();
    Serial.println(incoming);
  }
  
  
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  delay(95);
  digitalWrite(red_light_pin, LOW);
}

void eject(){
  servo1.write(ejectedAngle1);
  servo2.write(ejectedAngle2);
}

void lock(){
  servo1.write(normalAngle1);
  servo2.write(normalAngle2);
}
