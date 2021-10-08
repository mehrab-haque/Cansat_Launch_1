#include <Servo.h>

Servo servo;  
int normalAngle = 0;    
int ejectedAngle = 90;

void setup() {
  Serial.begin(9600);
  servo.attach(6);
}

void loop() {
  Serial.println("Hi");
  servo.write(normalAngle);
  delay(2000);
  servo.write(ejectedAngle);
  delay(2000);
}
