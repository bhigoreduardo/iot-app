#include <RH_ASK.h>
#include <SPI.h>
#include "env.h"  // All environment variables
#include "type.h" // All environment types

#define PINLED 13

RH_ASK driver;
String packet = "";
String fields[10];
int count = 0;

void setup() {
  Serial.begin(9600);
  setConfig();
}

void loop() {
  getMessage();
}

void setConfig() {
  pinMode(PINLED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  driver.init();
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
    if ((message[1] == recipient1st) || (message[1] == allRecipient)) {
      Serial.println(message[1]);
      if (message[4] == "LED") {
        digitalWrite(message[2].toInt(), message[3].toInt());
        digitalWrite(LED_BUILTIN, message[3].toInt());
      }
    }
  }
}