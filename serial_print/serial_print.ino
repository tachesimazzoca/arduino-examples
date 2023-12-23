void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  // The 2nd argument is base when printing numbers
  Serial.print("millis as base=10: ");
  Serial.print(currentMillis, DEC);
  Serial.println();
  Serial.print("millis as base=16: ");
  Serial.print(currentMillis, HEX);
  Serial.println();
  Serial.print("millis as base=2: ");
  Serial.print(currentMillis, BIN);
  Serial.println();
  // When using sprintf, the format paramaters must match corresponding values
  char buf[64];
  sprintf(buf, "correct: %lu, wrong: %d", currentMillis, currentMillis);
  Serial.println(buf);
  delay(1000);
}
