#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "secrets.h"

#define UDP_PORT 12345
#define SSID SECRET_SSID
#define PASSWD SECRET_PASS
// #define SOCK_PORT 124

WiFiUDP UDP;

char packet[255];
char reply[] = "Packet received!";

void setup(){
    Serial.begin(115200);
    delay(1000);
    WiFi.begin(SSID,PASSWD);
    while (WiFi.status() != WL_CONNECTED){delay(100);}

    Serial.println("");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    UDP.begin(UDP_PORT);
    Serial.print("Listening on UDP port");
    Serial.println(UDP_PORT);
}

void loop(){
  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize); 
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.print(WiFi.localIP());
    UDP.endPacket();
  }
}