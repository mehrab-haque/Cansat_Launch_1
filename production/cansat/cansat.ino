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
  
  
}
void loop() 
{
  temp=bmp.readTemperature();
  alt=bmp.readAltitude();
  pressure=bmp.readPressure();
//  LoRa.onReceive(onReceive);
//  LoRa.receive();
  receiveMessage(LoRa.parsePacket());
}

void receiveMessage(int packetSize) {
 
  if (packetSize == 0) return;        
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  Serial.println(packetSize);

  if (incoming[0]=='C' || incoming[0]=='B'){
    if(incoming[1]=='0'){
      String dataString="temp = "+String(temp)+" *C, pressure = "+String(pressure)+" Pa, altitude = "+String(alt)+" m";
      Serial.println(dataString);
   
      LoRa.beginPacket();
      LoRa.print(dataString);
      LoRa.endPacket();
    }
  }
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;        
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incoming[0]=='C' || incoming[0]=='B'){
    if(incoming[1]=='0'){
      String dataString="temp = "+String(temp)+" *C, pressure = "+String(pressure)+" Pa, altitude = "+String(alt)+" m";
      Serial.println(dataString);
      delay(200);
      LoRa.beginPacket();
      LoRa.print(dataString);
      LoRa.endPacket();
    }
  }
  
  
//  if(incoming[0]=='C' or incoming[0]=='B'){
//    Serial.println("Hi1");
//    switch(incoming[1]){
//      case '0':
//      
//        String dataString="temp = "+String(bmp.readTemperature())+" *C, pressure = "+bmp.readPressure()+" Pa, altitude = "+bmp.readAltitude()+" m";
//         Serial.println("Hiiiiii");
//         Serial.println(dataString);
//         LoRa.beginPacket();
//         LoRa.print(dataString);
//         LoRa.endPacket();
//    }
//  }
  
}
