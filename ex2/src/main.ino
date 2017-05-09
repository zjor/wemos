#include <Arduino.h>

#include "ESP8266WiFi.h"

const char* ssid = "********";
const char* password = "********";

WiFiServer server(80);

String index();

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}

void loop() {
  WiFiClient client = server.available(); 
  if (client) {
    Serial.println("\n[Client connected]");
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        if (line.length() == 1 && line[0] == '\n') {
          client.println(index());
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
  }
}

String index() {
  String html = 
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "<h1> Hello from Wemos </h1>" +
            "</html>" +
            "\r\n";
  return html;
}