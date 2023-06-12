#include <VirtualWire.h>
#include "env.h" // All environment variables
#include "type.h" // All environment types

#define PINRF 12

Packet packet;

void setup() {
  Serial.begin(9600);
  setConfig();
}

void loop() {
  if (digitalRead(recipient1stButton) == HIGH) {
    sendMessage(mobo, recipient1st, 13, 1, 1, 48.9);
    delay(300);
  }

  if (digitalRead(recipient2ndButton) == HIGH) {
    sendMessage(mobo, recipient2nd, 13, 1, 2, 38.9);
    delay(300);
  }

  if (digitalRead(recipient3rdButton) == HIGH) {
    sendMessage(mobo, recipient3rd, 13, 1, 3, 28.9);
    delay(300);
  }

  if (digitalRead(allRecipientButton) == HIGH) {
    sendMessage(mobo, allRecipient, 13, 0, 4, 18.9);
    delay(300);
  }
}

void setConfig() {
  // RF Transfer Config
  vw_set_tx_pin(PINRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  // OUT/IN Config
  pinMode(recipient1stButton, OUTPUT);
  pinMode(recipient2ndButton, OUTPUT);
  pinMode(recipient3rdButton, OUTPUT);
  pinMode(allRecipientButton, OUTPUT);
}

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
