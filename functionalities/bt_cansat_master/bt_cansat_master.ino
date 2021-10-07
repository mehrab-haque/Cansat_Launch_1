//Code for master module//


void setup() {
  
  Serial.begin(38400); // Default baud rate of the Bluetooth module
}
void loop() {
 Serial.write('1');
 delay(2000);
 Serial.write('0');
 delay(2000);
}
