#include <RH_ASK.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"
#include "env.h"

RH_ASK driver(2000, 2, 4, 5); // (Speed, Receive = [GPIO2/D4], Send = [GEPIO4/D2])
ESP8266WebServer server;

void setup() {
  Serial.begin(115200);
  setConfig();
}

void loop() {
  server.handleClient();
  delay(10);
}

void setConfig() {
  driver.init();
  Serial.println();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  IPAddress ipAddress = WiFi.softAPIP();
  Serial.print("Connect to: "+ String(ipAddress));

  server.on("/", handleRoot); 
  server.on("/led1on", handleled1on); server.on("/led1of", handleled1of);
  server.on("/led2on", handleled2on); server.on("/led2of", handleled2of);
  server.on("/led3on", handleled3on); server.on("/led3of", handleled3of);
  server.on("/led0on", handleled0on); server.on("/led0of", handleled0of);

  server.begin();
}

void handleRoot() {
  String page = MAIN_page;
  server.send(200, "text/html", page);
}

void handleled1on(){ server.send(200, "text/html", "ON"); sendMessage(mobo, recipient1st, 13, 1, "LED", 48.9); }
void handleled1of(){ server.send(200, "text/html", "OF"); sendMessage(mobo, recipient1st, 13, 0, "LED", 48.9); }
void handleled2on(){ server.send(200, "text/html", "ON"); sendMessage(mobo, recipient2nd, 13, 1, "LED", 48.9); }
void handleled2of(){ server.send(200, "text/html", "OF"); sendMessage(mobo, recipient2nd, 13, 0, "LED", 48.9); }
void handleled3on(){ server.send(200, "text/html", "ON"); sendMessage(mobo, recipient3rd, 13, 1, "LED", 48.9); }
void handleled3of(){ server.send(200, "text/html", "OF"); sendMessage(mobo, recipient3rd, 13, 0, "LED", 48.9); }
void handleled0on(){ server.send(200, "text/html", "ON"); sendMessage(mobo, allRecipient, 13, 1, "LED", 48.9); }
void handleled0of(){ server.send(200, "text/html", "OF"); sendMessage(mobo, allRecipient, 13, 0, "LED", 48.9); }

void sendMessage(unsigned long mobo, unsigned long recipient, int pinout, int value, int variable, float data) {
  packet.mobo = mobo;
  packet.recipient = recipient;
  packet.pinout = pinout;
  packet.value = value;
  packet.variable = variable;
  packet.data = data;

  vw_send((uint8_t *)&packet, sizeof(packet));
  vw_wait_tx();
}