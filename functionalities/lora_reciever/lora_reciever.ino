#include <SPI.h>
#include <LoRa.h>
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
