#include "pitches.h"

const int buttonPin = 2;
const int speakerPin = 8;

const int melody[][2] = {
  { NOTE_A3, 160 },
  { NOTE_C4, 160 },
  { NOTE_DS4, 160 },
  { NOTE_FS4, 160 },
  { NOTE_A4, 160 },
  { NOTE_OFF, 160 }
};
const int numNotes = 6;
const int baseBpm = 120;
const int bpm = 160;

void setup() {
  pinMode(buttonPin, INPUT);
}

void loop() {
  for (int i = 0; i < numNotes; i++) {
    // Play notes while the button is pressed
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {
      return;
    }
    int duration = melody[i][1] * baseBpm / bpm;
    tone(speakerPin, melody[i][0], duration);
    delay(duration);
    noTone(speakerPin);
  }
}