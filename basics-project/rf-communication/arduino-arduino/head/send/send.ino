#include <RH_ASK.h>
#include <SPI.h>
#include "env.h"  // All environment variables
#include "type.h" // All environment types

#define DELAYTIME = 5000

RH_ASK driver;

void setup()
{
  Serial.begin(9600);
  driver.init();
}

void loop()
{
  sendMessage(mobo, recipient1st, 13, 1, 1, 48.9);
  delay(DELAYTIME);

  sendMessage(mobo, recipient2nd, 13, 1, 2, 38.9);
  delay(DELAYTIME);

  sendMessage(mobo, recipient3rd, 13, 1, 3, 28.9);
  delay(DELAYTIME);

  sendMessage(mobo, allRecipient, 13, 0, 4, 18.9);
  delay(DELAYTIME);
}

void sendMessage(unsigned long mobo, unsigned long recipient, int pinout, int value, int variable, float data)
{
  char *msg = "|" + mobo + "|" + recipient + "|" + pinout + "|" + value + "|" + variable + "|" + data;
  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
}