#include <Servo.h>

Servo servo1;  
int normalAngle1 = 0;    
int ejectedAngle1 = 90;

Servo servo2;  
int normalAngle2 = 0;    
int ejectedAngle2 = 90;

void setup() {
  Serial.begin(9600);
  servo1.attach(5);
  servo2.attach(6);
}

void loop() {
  Serial.println("Hi");
  servo1.write(normalAngle1);
  servo2.write(normalAngle2);
  delay(2000);
  servo1.write(ejectedAngle1);
  servo2.write(ejectedAngle2);
  delay(2000);
}
