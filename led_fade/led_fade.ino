const int ledPin = 9;
const int depth = 5;
const int duration = 30;

int brightness = 0;
int fade = 1;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (brightness < 0) {
    fade = 1;
    brightness = 0;
  } else if (brightness > 255) {
    fade = -1;
    brightness = 255;
  }
  analogWrite(ledPin, brightness);
  brightness = brightness + (fade * depth);
  delay(duration);
}