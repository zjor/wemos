#include <Arduino.h>
#include <EEPROM.h>
#include "ESP8266WiFi.h"

String ssid, password;

String readFromSerial(String title) {
  Serial.printf("%s: ", title.c_str());
  char c;
  String data;
  while (Serial.available() > 0) {
    c = Serial.read();
    Serial.print(c);
    if (c == 'x') {
      break;
    }
    data += c;

  }
  return data;
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n**\tEx4\t**\t");

  ssid = readFromSerial("ssid");
  Serial.println("Data read: " + ssid);

}

void loop() {

}
