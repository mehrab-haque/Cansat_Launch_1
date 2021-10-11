#include <SPI.h>
#include <LoRa.h> 

int red_light_pin= 7;
int green_light_pin = 6;

bool r=false;

void setup() 
{
  pinMode(red_light_pin, OUTPUT);
  greenLight();
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
    

    delay(1000);
    LoRa.onReceive(onReceive);
    LoRa.receive();
    
  }
  
  if(r){
    redLight();
    r=false;
  }
  
 
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;         
  String incoming = "";

  r=true;

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  Serial.println();
  Serial.println("########data recieved########");
  Serial.println(incoming);
  Serial.println("########completed########");
  
  
}

void onTxDone() {
  redLight();
}

void greenLight(){
  digitalWrite(green_light_pin, HIGH);
  delay(95);
  digitalWrite(green_light_pin, LOW);
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  delay(95);
  digitalWrite(red_light_pin, LOW);
}
