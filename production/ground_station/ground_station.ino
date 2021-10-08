#include <SPI.h>
#include <LoRa.h> 

void setup() 
{
  Serial.begin(9600);
  Serial.println("ground station initializing...");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa initialized...");
  LoRa.onReceive(onReceive);
  LoRa.receive();
  Serial.println("LoRa listening...");
  Serial.println("ground station initialized...");
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
  Serial.println("########data recieved########");
  Serial.println(incoming);
  Serial.println("########completed########");
  Serial.println();
}
