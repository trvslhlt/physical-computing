/*
 * This sketch translates numerals 0-9 into Morse Code flashes on the Arduino Fio's built-in LED
 */

// This global varable stores the numeral the Arduino will flash on its LED.
// It is initialized with the null character to indicate there is no numeral to flash.
char numeralToFlash = '\0';

void setup() {
  // Begin serial communication. This allows us to send user input text to the Arduino.
  Serial.begin(9600); // baud rate
}

void loop() {
  // if we have nothing to flash on the LED, return
  if (numeralToFlash == '\0') {
    return;  
  } else {
    flashNumeral(numeralToFlash);
    numeralToFlash = '\0'; // clear the numeral that we just flashed on the LED
  }
}

void serialEvent() {
  // begin with the assumption that we received no valid numerals in the serial event
  char readChar = '\0';
  // track the number of input characters. This sketch is only intended to support single numeral input; entering more than one numeral is a NOP
  int readCharCount = 0;

  // While data is available on the serial port...
  while (Serial.available()) {
    // ... read a byte as a `char`
    readChar = (char)Serial.read();
    // increment the characters read count
    readCharCount += 1;
  }
  // if we received exactly 1 character and that character is a numeral, set `numeralToFlash` to that character.
  // Wait for the next `loop` call to see the numeral flashed on the LED
  numeralToFlash = (readCharCount == 1 && isDigit(readChar) && numeralToFlash == '\0') ? readChar : numeralToFlash;
}

// Orchestrates the "on" and "off" commands to the LED, and the timing of those commands.
void flashNumeral(char numeral) {
  int patternLength = 10;
  int pattern[patternLength];
  morsePatternForNumeral(numeral, pattern);
  for (int i = 0; i < patternLength; i++) {
    if (i % 2) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);  
    }
    delay(pattern[i]);
  }
}

// Assigns timing patterns for a given numeral to a provided `int` array
// e.g. for numeral = 1 -> [500, 200, 500, 200, 500, 200, 500, 200, 500, 200]
// NOTE: I don't know the best way to work with C++ collections yet. This can be condensed once I figure that out.
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

// convenience function while I get used to C++
void assignElements(int len, int *target, int *donor) {
    for (int i = 0; i < len; i++) {
      target[i] = donor[i];
    }
}
