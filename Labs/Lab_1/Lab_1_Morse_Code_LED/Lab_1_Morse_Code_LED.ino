/*
 * This sketch translates numerals 0-9 into Morse Code flashes on the Arduino Fio's built-in LED
 */

String numeralToFlash = "";

void setup() {
  Serial.begin(9600); // baud rate
  numeralToFlash.reserve(1); // only storing a single character
}

void loop() {
  if (numeralToFlash.length() == 0) { // if we have a number to flash
    return;  
  }
  Serial.println(numeralToFlash);
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  numeralToFlash = "";
}

void serialEvent() {
  char readChar = "";
  int readCharCount = 0;
  
  while (Serial.available()) {
    readChar = (char)Serial.read();
    readCharCount += 1;
  }
  
  if (readCharCount == 1 && isDigit(readChar) && !numeralToFlash.length()) {
    numeralToFlash = readChar;
  } else {
    numeralToFlash = "";
  }
}

