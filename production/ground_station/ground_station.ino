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
  Serial.println("LoRa listening...");
  Serial.println("ground station initialized...");
}
void loop() 
{
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
  Serial.println("########data recieved########");
  Serial.println(incoming);
  Serial.println("########completed########");
  Serial.println();
  
}

void greenLight(){
  digitalWrite(red_light_pin, LOW);
  digitalWrite(green_light_pin, HIGH);
}

void redLight(){
  digitalWrite(red_light_pin, HIGH);
  digitalWrite(green_light_pin, LOW);
  delay(95);
  greenLight();
}
