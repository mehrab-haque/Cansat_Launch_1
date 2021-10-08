#include <SPI.h>
#include <LoRa.h>

long lastSendTime = 0;        
int interval = 1500;   

void setup() 
{
  Serial.begin(9600);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.onReceive(onReceive);
  LoRa.receive();
}
void loop() 
{
//  if (millis() - lastSendTime > interval) {
//      lastSendTime = millis(); 
//       LoRa.beginPacket();                   // start packet
//      LoRa.write("2");              // add destination address
//      LoRa.endPacket();                  
//      LoRa.receive();                     
//    }
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;         
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}
