const int sensorPin = A0;
const int ledPin = 9;
const int brightnessMin = 0;
const int brightnessMax = 255;
const unsigned long calibrationTime = 5000;

int sensorMin = -1;
int sensorMax = -1;

void setup() {
  Serial.begin(9600);
  // Turn the buit-in LED on while calibrating
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  while (millis() < calibrationTime) {
    int sensorValue = analogRead(sensorPin);
    if (sensorMin == -1 || sensorMin > sensorValue) {
      sensorMin = sensorValue;
    }
    if (sensorMax == -1 || sensorMax < sensorValue) {
      sensorMax = sensorValue;
    }
  }
  Serial.print("sensorMin: ");
  Serial.println(sensorMin, DEC);
  Serial.print("sensorMax: ");
  Serial.println(sensorMax, DEC);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  // Map the sensorValue to a brightness depth
  int depth = map(constrain(sensorValue, sensorMin, sensorMax),
                  sensorMin, sensorValue, brightnessMin, brightnessMax);
  // The lower the sensorValue is, the brighter the LED gets 
  analogWrite(ledPin, brightnessMax - depth);
  // Avoid flickering
  delay(100);
}
