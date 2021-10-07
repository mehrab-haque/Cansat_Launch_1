//Code for Slave module//

#define ledPin 13
int dataFromMaster = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(38400); // Default baud rate of the Bluetooth module
}
void loop() {
 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
   dataFromMaster = Serial.read(); // Reads the data from the serial port and store it in dataFromMaster variable
   Serial.println(dataFromMaster);
 }
 // Controlling the led
 if (dataFromMaster == '1') {
  digitalWrite(ledPin, HIGH); // LED ON
 }
 else if (dataFromMaster == '0') {
  digitalWrite(ledPin, LOW); // LED    OFF
 }
 delay(10);
}
