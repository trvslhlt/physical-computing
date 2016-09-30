int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
int buttonPin = 13;

bool buttonIntent = false; // true if pressed
bool lastButtonState = false;
int DOT = 0;
int DASH = 1;
int dotDashPattern[5] = { -1, -1, -1, -1, -1};

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long dotToDashTime = 300;
unsigned long intentTimeout = 3000;

unsigned long pressTime = 0;
unsigned long releaseTime = 0;

int rowPin[5] = {3, 4, 1, 6, 7};
int colPin[5] = {2, 0, 5};

int code[10][5] = {{1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1},
  {0, 0, 1, 1, 1},
  {0, 0, 0, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 0, 0, 0},
  {1, 1, 1, 0, 0},
  {1, 1, 1, 1, 0}
};

int led[10][5][3] = {{{1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  { {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  },
  { {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1}
  },
  { {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  { {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  { {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  { {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  { {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  { {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  { {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  }
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  determineButtonIntent();
  checkForTimeout();
}

void determineButtonIntent() {
  bool reading = digitalRead(buttonPin);
  //if the reading has changed since the last loop...
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    lastButtonState = reading;
    return;
  }

  unsigned long currentTime = millis();
  //if the not enough time has passed to be certain of intent...
  if (currentTime - lastDebounceTime <= debounceDelay) {
    return;
  }

  //update the button intent
  bool newButtonIntent = lastButtonState;
  // if the intent has changed, update
  if (newButtonIntent != buttonIntent) {
    buttonIntent = newButtonIntent;
    changeButtonToIntent(newButtonIntent);
  }
}

void changeButtonToIntent(bool pressed) {
  if (pressed) {
    pressTime = millis();
    return;
  }
  releaseTime = millis();
  int symbol = (releaseTime - pressTime < dotToDashTime) ? DOT : DASH;
  for (int i = 0; i < 5; i ++) {
    if (dotDashPattern[i] == -1) {
      dotDashPattern[i] = symbol;
      if (i == 4) {
        completedPattern();
      }
      break;
    }
  }
}

void completedPattern() {
  int numeral = -1;
  for (int c = 0; c < 10; c++) {
    numeral = c;
    for (int d = 0; d < 5; d++) {
      if (code[c][d] != dotDashPattern[d]) {
        numeral = -1;
        break;
      }
    }
    if (numeral != -1) {
      break;
    }
  }
  if (numeral != -1) {
    animateLEDs(numeral);
  }
  resetPattern();
}

void resetPattern() {
  for (int i = 0; i < 5; i++) {
    dotDashPattern[i] = -1;
  }
}

void checkForTimeout() {
  if (releaseTime > pressTime) {
    if (millis() - releaseTime > intentTimeout) {
      releaseTime = millis();
      for (int i = 0; i < 5; i++) {
        dotDashPattern[i] = -1;
      }
    }
  }
}

void animateLEDs(int numeral) {
  // Using persistence of vision to show digits
  for (int iter = 0; iter < 2000; iter++) {
    for (int j = 0; j < 5; j++) {
      digitalWrite(latchPin, LOW);
      for (int i = 0; i < 8; i++) {
        digitalWrite(clockPin, LOW);
        digitalWrite(dataPin, LOW);
        if (i == rowPin[j]) digitalWrite(dataPin, HIGH);
        for (int k = 0; k < 3; k++) {
          if (i == colPin[k] && led[numeral][j][k] == 0) {
            digitalWrite(dataPin, HIGH);
          }
        }
        digitalWrite(clockPin, HIGH);
      }
      digitalWrite(latchPin, HIGH);
    }
  }

  //clear the display
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
}
