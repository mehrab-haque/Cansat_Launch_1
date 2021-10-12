#include <SPI.h>
#include <LoRa.h> 

int red_light_pin= 3;
int yellow_light_pin = 7;

bool y=false,r=false;

void setup() 
{
  pinMode(red_light_pin, OUTPUT);
  pinMode(yellow_light_pin, OUTPUT);
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
  //LoRa.onTxDone(onTxDone);
  Serial.println("LoRa listening...");
  Serial.println("ground station initialized...");
}
void loop() 
{

  if (Serial.available() > 0) {
    String incomingString = Serial.readString().substring(0,2);
    LoRa.beginPacket();
    LoRa.print(incomingString);
    LoRa.endPacket();
    Serial.println();
    Serial.println("$$$$$$$$command sent$$$$$$$$");
    Serial.println(incomingString);
    Serial.println("$$$$$$$$command end$$$$$$$$");
    Serial.println();
    
    redLight();
  
    delay(1000);
    LoRa.onReceive(onReceive);
    LoRa.receive();
    
  }
  
  if(r){
    redLight();
    r=false;
  }
  if(y){
    yellowLight();
    y=false;
  }
  
 
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;         
  String incoming = "";

  y=true;

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  Serial.println(incoming);
}

void yellowLight(){
  digitalWrite(yellow_light_pin, HIGH);
  delay(95);
  digitalWrite(yellow_light_pin, LOW);
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  delay(95);
  digitalWrite(red_light_pin, LOW);
}
