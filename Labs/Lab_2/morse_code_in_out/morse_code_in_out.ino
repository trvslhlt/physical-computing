int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
byte leds = 1;
 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  leds = B11111111;
  for (int i = 1; i < 8; i++) {
    bitClear(leds, i);
    bitSet(leds, i - 1);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}

