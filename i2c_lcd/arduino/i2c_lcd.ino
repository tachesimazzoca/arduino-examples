#include <Wire.h>

#define LCD_ADDR 0x3E
#define CGRAM_NUM 6
#define CGRAM_ICON_HEIGHT 7

char msg[] = "Hello AMQ1602!";

void setup() {
  Wire.begin();
  setupLCD();
  setupCGRAM();
}

void loop() {
  // Retern Home
  writeCommand(0x02);

  // Write the message in the 1st line
  writeCommand(0x80);
  int msgLength = sizeof(msg) / sizeof(msg[0]);
  for (int i = 0; i < msgLength; i++) {
    writeData(msg[i]);
  }

  // Write CGRAM characters in the 2nd line
  const int animationDelay = 50;
  for (int j = 0; j < 16; j++) {
    int addr = 0x80 + 0x40 + j;
    for (int i = 0; i < CGRAM_NUM; i++) {
      writeCommand(addr);
      writeData(i);
      delay(animationDelay);
    }
    for (int i = 0; i < CGRAM_NUM; i++) {
      writeCommand(addr);
      writeData(CGRAM_NUM - 1 - i);
      delay(animationDelay);
    }
  }
}

void writeData(byte t_data) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
}

void writeCommand(byte t_command) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}

void setupLCD() {
  delay(100);

  // Refer extension instruction table (0011 1001)
  writeCommand(0x39);
  delay(20);

  // Internal OSC freqency
  writeCommand(0x14);
  delay(20);

  // 0x7[0-F]: Contrast set C3-C0
  writeCommand(0x7A);
  delay(20);
  // 0x5[0-F]: ICON display, Booster circuit, Contrast set C5-C4
  writeCommand(0x54);
  delay(20);

  // Follower control
  writeCommand(0x6C);
  delay(20);

  // Refer normal instruction table (0011 1000)
  writeCommand(0x38);
  delay(20);

  // Display ON/OFF
  //   0x0C: Display ON
  //   0x0D: Cursor Blink ON
  //   0x0E: Cursor ON
  //   0x0F: Cursor & Blink ON
  writeCommand(0x0C);
  delay(20);

  // Clear Display
  writeCommand(0x01);
  delay(20);

  // 0x06: Shift the display to the right
  // 0x07: Shift the display to the left
  writeCommand(0x06);
  delay(20);
}

void setupCGRAM() {
  // Icons in 5x7 dots
  int icons[CGRAM_NUM][CGRAM_ICON_HEIGHT] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x04, 0, 0, 0 },
    { 0, 0, 0x0e, 0x0a, 0x0e, 0, 0 },
    { 0, 0, 0x0e, 0x0e, 0x0e, 0, 0 },
    { 0, 0x1f, 0x11, 0x11, 0x11, 0x1f, 0 },
    { 0, 0x1f, 0x11, 0x15, 0x11, 0x1f, 0 }
  };
  writeCommand(0x40);
  for (int j = 0; j < CGRAM_NUM; j++) {
    writeData(0);
    for (int i = 0; i < CGRAM_ICON_HEIGHT; i++) {
      writeData(icons[j][CGRAM_ICON_HEIGHT -1 - i]);
    }
   }
}