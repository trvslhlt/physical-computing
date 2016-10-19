#include <SoftwareSerial.h>


int rxPin = 0; // specific to the FIO
int txPin = 1; // specific to the FIO
int pwmPin = 13;
int pwmValue = 0;
char newLine = '\n';
SoftwareSerial xbee(rxPin, txPin);

void setup() {
  pinMode(pwmPin, INPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  xbee.begin(9600);
}

void loop() {
  readDistance();
  transmitDistance();
}

void readDistance() {
  pwmValue = pulseIn(pwmPin, HIGH);  
}

void transmitDistance() {
  xbee.print(pwmValue);  
  xbee.print(newLine);
}

