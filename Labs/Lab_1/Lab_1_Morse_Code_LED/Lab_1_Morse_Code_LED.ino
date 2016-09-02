/*
 * This sketch translates numerals 0-9 into Morse Code flashes on the Arduino Fio's built-in LED
 */

char numeralToFlash = '\0';

void setup() {
  Serial.begin(9600); // baud rate
}

void loop() {
  if (numeralToFlash == '\0') {
    return;  
  } else {
    flashNumeral();
    numeralToFlash = '\0';
  }
}

void serialEvent() {
  char readChar = '\0';
  int readCharCount = 0;
  
  while (Serial.available()) {
    readChar = (char)Serial.read();
    readCharCount += 1;
  }
  
  if (readCharCount == 1 && isDigit(readChar) && numeralToFlash == '\0') {
    numeralToFlash = readChar;
  } else {
    numeralToFlash = '\0';
  }
}

void flashNumeral() {
  Serial.println(numeralToFlash);
  int patternLength = 10;
  int pattern[patternLength];
  morsePatternForNumeral(numeralToFlash, pattern);
  for (int i = 0; i < patternLength; i++) {
    if (i % 2) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);  
    }
    delay(pattern[i]);
  }
}

void morsePatternForNumeral(char numeral, int *pattern) {
  int dot = 100;
  int dash = 500;
  int rest = 200;

  if (numeral == '0') {
    int morsePattern[10] = {dash, rest, dash, rest, dash, rest, dash, rest, dash, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '1') {
    int morsePattern[10] = {dot, rest, dash, rest, dash, rest, dash, rest, dash, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '2') {
    int morsePattern[10] = {dot, rest, dot, rest, dash, rest, dash, rest, dash, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '3') {
    int morsePattern[10] = {dot, rest, dot, rest, dot, rest, dash, rest, dash, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '4') {
    int morsePattern[10] = {dot, rest, dot, rest, dot, rest, dot, rest, dash, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '5') {
    int morsePattern[10] = {dot, rest, dot, rest, dot, rest, dot, rest, dot, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '6') {
    int morsePattern[10] = {dash, rest, dot, rest, dot, rest, dot, rest, dot, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '7') {
    int morsePattern[10] = {dash, rest, dash, rest, dot, rest, dot, rest, dot, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '8') {
    int morsePattern[10] = {dash, rest, dash, rest, dash, rest, dot, rest, dot, rest};
    assignElements(10, pattern, morsePattern);
  } else if (numeral == '9') {
    int morsePattern[10] = {dash, rest, dash, rest, dash, rest, dash, rest, dot, rest};
    assignElements(10, pattern, morsePattern);
  }
}

void assignElements(int len, int *target, int *donor) {
    for (int i = 0; i < len; i++) {
      target[i] = donor[i];
    }
}
