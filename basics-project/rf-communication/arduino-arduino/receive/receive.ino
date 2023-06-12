#include <VirtualWire.h>
#include "env.h" // All environment variables
#include "type.h" // All environment types

#define PINRF 12
#define PINLED 13

Packet packet;
uint8_t buffer[sizeof(packet)];
uint8_t lengthBuffer = sizeof(packet);

void setup() {
  Serial.begin(9600);
  setConfig();
}

void loop() {
  if (vw_have_message()) {
    getMessage();
  }
}

void setConfig() {
  // RF Recepient Config
  vw_set_rx_pin(PINRF);
  vw_setup(2000);
  vw_rx_start();

  // OUT/IN Config
  pinMode(PINLED, OUTPUT);
}

void getMessage() {
  // Decode
  vw_get_message(buffer, &lengthBuffer);
  memcpy(&packet, &buffer, &lengthBuffer);

  Serial.print("Mobo: ");         Serial.print(packet.mobo);
  Serial.print(", Recipient: ");  Serial.print(packet.recipient);
  Serial.print(", Pinout: ");     Serial.print(packet.pinout);
  Serial.print(", Value: ");      Serial.print(packet.value);
  Serial.print(", Variable: ");   Serial.print(packet.variable);
  Serial.print(", Data: ");       Serial.print(packet.data);

  if (packet.mobo == mobo & (packet.recipient == recipient1st || packet.recipient == allRecipient)) {
    digitalWrite(packet.pinout, packet.value);
  }
}