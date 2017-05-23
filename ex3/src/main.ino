#include <SPI.h>
#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example

int SCREEN_WIDTH = oled.getLCDWidth();
int SCREEN_HEIGHT = oled.getLCDHeight();

bool initialized = false;

void setup() {
  Serial.begin(115200);

  oled.begin();
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.setCursor(0, 0);
  oled.print("Start typing...");
  oled.display();
}

void loop() {
  if (Serial.available() > 0) {
    if (!initialized) {
      oled.clear(PAGE);
      oled.setCursor(0, 0);
      initialized = true;
    }
    int data = Serial.read();
    if (data == '\n') {
      initialized = false;
    }
    oled.printf("%c", data);
    oled.display();
  }
}
