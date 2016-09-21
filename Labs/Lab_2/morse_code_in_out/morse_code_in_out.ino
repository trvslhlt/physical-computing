//https://www.arduino.cc/en/Tutorial/Debounce


int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
int buttonPin = 13;
bool buttonIntent = false; // not pressed
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 0;

 
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() { 
  determineButtonIntent();
  
}

void animateLEDs() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(latchPin, LOW);    
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, LOW);
    digitalWrite(dataPin, (i == 0) ? (HIGH) : (LOW));
    digitalWrite(clockPin, HIGH);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}

// debounce button action
void determineButtonIntent() {
  bool buttonPressed = digitalRead(buttonPin);
  if (buttonPressed != buttonIntent) {
    lastDebounceTime = millis();
  }

  // if we are confident we know the state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (buttonIntent != buttonPressed) {
      changeButtonIntent(buttonPressed);
    }
    
  }
}

void changeButtonIntent(bool pressed) {
  buttonIntent = pressed;
  if (buttonIntent) {
    Serial.print("pressed"); 
  } else {
    Serial.print("-------");  
  }
}

