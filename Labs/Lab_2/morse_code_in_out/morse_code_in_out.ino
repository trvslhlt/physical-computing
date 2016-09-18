//https://www.arduino.cc/en/Tutorial/ShftOut23

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, HIGH);
    digitalWrite(clockPin, HIGH); 
  }
  digitalWrite(latchPin, HIGH);
}

//  byte data = B0001111;
//  digitalWrite(latchPin, LOW);
//  delay(500);
//  shiftOut(data);
//  digitalWrite(latchPin, HIGH);
//  delay(1000);
//}

void shiftOut(byte myDataOut) {
  
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, LOW);
  int pinState = LOW;
  
  for (int i = 7; i >= 0; i--) {
    if ( myDataOut & (1<<i) ) {
      pinState = HIGH;
    } else {  
      pinState = LOW;
    }
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, HIGH);
    digitalWrite(dataPin, LOW); // reset to prevent "bleed through"
  }
  digitalWrite(clockPin, LOW);  
}
