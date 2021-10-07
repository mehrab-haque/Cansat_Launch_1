#include <SPI.h>
#include <LoRa.h>

int incomingByte = 0; 

void setup() 
{
  Serial.begin(9600);
  Serial.println("ground station initializing...");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully...");
  LoRa.onReceive(onReceive);
  LoRa.receive();
}
void loop() 
{
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    LoRa.beginPacket();
    LoRa.print(command);
    LoRa.endPacket();
    Serial.print("command propagated : ");
    Serial.print(command);
    Serial.println();
  }
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;         
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  
  if(incoming[0]!='R' and incoming[0]!='C' and incoming[0]!='B'){
    Serial.println();
    Serial.println("########Data Recieved########");
    Serial.println(incoming);
    Serial.println("########Completed########");
    Serial.println();
  }
  
}
