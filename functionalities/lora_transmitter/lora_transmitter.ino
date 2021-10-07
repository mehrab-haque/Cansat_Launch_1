#include <SPI.h>
#include <LoRa.h>
int counter = 0;
void setup() 
{
  Serial.begin(9600);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while(1);
  }
}
void loop() 
{
  String msg = "e";
  Serial.print("Sending message ");
  Serial.println(msg);
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
  delay(5000);
}
