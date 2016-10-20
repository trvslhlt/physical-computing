#include <SoftwareSerial.h>


int rxPin = 0; // specific to the FIO
int txPin = 1; // specific to the FIO
int pwmPin = 13; // allows us to see the pwm input on the builtin LED
int pwmValue = 0;
const int buttonPin = 12;
int buttonState = 0;
char measurementDelimiter = '\n'; // indicates a distance measurement communication is complete
SoftwareSerial xbee(rxPin, txPin); // the interface to the XBee

void setup() {
  pinMode(pwmPin, INPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  xbee.begin(9600);
}

void loop() {
  readDistance();
  buttonState = digitalRead(buttonPin);
  // if the button is pressed...
  if (buttonState == HIGH) {
    transmitDistance();
    delay(500);
  }
}

void readDistance() {
  pwmValue = pulseIn(pwmPin, HIGH);  
}

void transmitDistance() {
  xbee.print(pwmValue);  
  xbee.print(measurementDelimiter);
}
