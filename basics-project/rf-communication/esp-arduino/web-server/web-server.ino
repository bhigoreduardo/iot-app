#include <RH_ASK.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#include "env.h"

#define PINLED 13

RH_ASK driver(2000, 2, 4, 5);
ESP8266WebServer server(80);

String packet = "";
String fields[10];
int count = 0;
int pinValue = 0;
int led1st, led2nd, led3rd;

const char* ssid = ssid;
const char* password = pass;

/* Set IpAdrress */
// IPAddress ip(192, 168 , 0, 15);
// IPAddress gateway(192, 168, 0, 1);
// IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  setConfig();
}

void loop(){
  server.handleClient();
  delay(10);
  getMessage();
}

void setConfig() {
  driver.init();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to: ", ssid);
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/count", handleCount);
  server.on("/led1st", handleLed1st);
  server.on("/led2nd", handleLed2nd);
  server.on("/led3rd", handleLed3rd);

  server.begin();
  Serial.println("HTTP server started");
}
void getMessage() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if(driver.recv(buf, &buflen)) {
    Serial.println("========================");
    packet = "";
    count = 0;

    while (count < buflen) {
      packet += (char)buf[i];
      count++;
    }
  }

  if (packet.length() > 0) {
    Serial.println(packet);
    count = 0;

    while (count < 10) {
      int firstPipe = packet,indexOf("|");
      int lastPipe = packet,indexOf("|", firstPipe + 1);
      String message = packet.substring(firstPipe + 1, lastPipe);
      packet.remove(firstPipe + 1, lastPipe)

      fields[count] = message;
      count++;
    }

    executeMessage(fields);
    packet = "";
  }
}
void executeMesage(String message[]) {
  // message[0]: mobo = 100000
  // message[1]: recipient = 100001
  // message[2]: pinout = 13 [0-99]
  // message[3]: value = [0-1]
  // message[4]: variable = LED
  // message[4]: data = 37.11

  if (message[0] == mobo) {
    Serial.println(message[1]);

    if (message[1] == allRecipient) {
      if (message[4] == "LED") {
        led1st = message[3].toInt(); led2nd = message[3].toInt(); led3rd = message[3].toInt();
      }
    }

    if (message[1] == recipient1st) {
      if (message[4] == "LED") {
        led1st = message[3].toInt();
      }
    }

    if (message[1] == recipient2nd) {
      if (message[4] == "LED") {
        led2nd = message[3].toInt();
      }
    }

    if (message[1] == recipient3rd) {
      if (message[4] == "LED") {
        led3rd = message[3].toInt();
      }
    }

    Serial.print("led1st: "); Serial.println(led1st);
    Serial.print("led2nd: "); Serial.println(led2nd);
    Serial.print("led3rd: "); Serial.println(led3rd);
    Serial.println("==========================================================");
  }
}
void handleRoot() { String page = MAIN_page; server.send(200, "text/html", page); }
void handleCount() { pinValue++; String counter = String(pinValue); server.send(200, "text/plane", counter); }
void handleLed1st() { String led1stState; if (led1st == 1) { led1stState = "On"; } else { led1stState = "Off" } server.send(200, "text/plane", led1stState); }
void handleLed2nd() { String led2ndState; if (led2nd == 1) { led2ndState = "On"; } else { led2ndState = "Off" } server.send(200, "text/plane", led2ndState); }
void handleLed3rd() { String led3rdState; if (led3rd == 1) { led3rdState = "On"; } else { led3rdState = "Off" } server.send(200, "text/plane", led3rdState); }
