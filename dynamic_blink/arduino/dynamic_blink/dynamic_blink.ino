const int buttonPin = 2;
const unsigned long debounceDelay = 100;

unsigned long lastBlinkMillis = 0;
unsigned long interval = 1000;
int ledState = LOW;

int lastButtonState = LOW;
unsigned long debounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(buttonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Detect interval with buttonPin
  int buttonState = digitalRead(buttonPin);
  if (lastButtonState != buttonState) {
    if (buttonState == HIGH) {
      Serial.println("button: on");
      debounceTime = currentMillis;
    } else {
      Serial.println("button: off");
      if ((currentMillis - debounceTime) >= debounceDelay) {
        interval = currentMillis - debounceTime;
        printInterval(interval);
      }
    }
    lastButtonState = buttonState;
  }

  // Blink without blocking
  if (currentMillis - lastBlinkMillis >= interval) {
    lastBlinkMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}

void printInterval(unsigned long ul) {
  Serial.print("interval: ");
  Serial.println(ul, DEC);
}
