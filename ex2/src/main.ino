#include <Arduino.h>

#include "ESP8266WiFi.h"

const char* ssid = "UPC92A2B1A";
const char* password = "X6ved8fseteu";

WiFiServer server(80);
int ledStatus = HIGH;

String index();

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
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
  Serial.printf("Web server started, open http://%s in a web browser\n", WiFi.localIP().toString().c_str());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n[Client connected]");
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);

        if (line.indexOf("GET /toggle") != -1) {
          ledStatus = ledStatus == HIGH ? LOW : HIGH;
          digitalWrite(BUILTIN_LED, ledStatus);
        }

        if (line.length() == 1 && line[0] == '\n') {
          client.println(index(ledStatus));
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

String index(int ledStatus) {
  String color, label;
  if (ledStatus == HIGH) {
    color = String("green");
    label = String("ON");
  } else {
    color = String("grey");
    label = String("OFF");
  }

  String html =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "\r\n" +
            "<!DOCTYPE html>\n" +
            "<html>\n" +
            "<head>\n" +
            "<style>\n" +
            "\n" +
            "body {\n" +
            "     width: 400px;\n" +
            "     margin: 0 auto;\n" +
            "}\n" +
            "\n" +
            ".left {\n" +
            "     float: left;\n" +
            "     line-height: 16px;\n" +
            "     vertical-align: middle;\n" +
            "     margin-right: 8px;\n" +
            "}\n" +
            "\n" +
            ".clearfix {\n" +
            "  overflow: auto;\n" +
            "}\n" +
            "\n" +
            ".clearfix:after {\n" +
            "     content: \"\";\n" +
            "     clear: both;\n" +
            "     display: block;\n" +
            "}\n" +
            "\n" +
            ".button {\n" +
            "     padding: 8px;\n" +
            "     text-align: center;\n" +
            "}\n" +
            "\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "\n" +
            "<h1>Wemos LED control</h1>\n" +
            "\n" +
            "<div class=\"clearfix\">\n" +
            "     <div class=\"left\">LED status: </div>\n" +
            "\n" +
            "     <div class=\"left\">\n" +
            "          <svg version=\"1.1\" baseProfile=\"full\" width=\"16\" height=\"16\" xmlns=\"http://www.w3.org/2000/svg\">\n" +
            "            <circle cx=\"8\" cy=\"8\" r=\"8\" fill=\"" + color + "\" />\n" +
            "          </svg>     \n" +
            "     </div>\n" +
            "     <div class=\"left\">" + label + "</div>\n" +
            "</div>\n" +
            "\n" +
            "<div class=\"button\">\n" +
            "     <a href=\"/toggle\">Toggle</a>\n" +
            "</div>\n" +
            "</body>\n" +
            "</html>" +
            "\r\n";
  return html;
}
