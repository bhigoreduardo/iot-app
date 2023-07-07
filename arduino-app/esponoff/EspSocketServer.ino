#include <ESP8266WiFi.h>
#include "secrets.h"

#define SSID SECRET_SSID
#define PASSWD SECRET_PASS
#define SOCK_PORT 123

WiFiServer sockServer(SOCK_PORT);

void setup(){
    // Serial.begin(9600);
    Serial.begin(115200);
    delay(1000);
    WiFi.begin(SSID,PASSWD);
    while (WiFi.status() != WL_CONNECTED){delay(100);}

    Serial.println("");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    sockServer.begin();
}

void loop(){
    WiFiClient client = sockServer.available();
    if (client){
        unsigned int firstLimit = 1000;
        unsigned int lastLimit = 1000;
        while (client.connected() && --firstLimit > 0){
            delay(200);
            String threeWayBuffer = String();
            bool hasData = false;
            
            while (client.available() > 0 && --lastLimit > 0){
              // uint8_t value = client.read();
              threeWayBuffer.concat((char)client.read());
              hasData = true;

              if (hasData) {
                Serial.println(threeWayBuffer);
                if (threeWayBuffer.equals("ACK")) {
                  client.print("SYN-ACK");
                }
              }
              // Serial.print(client.available());
              // Serial.print(" : ");
              // Serial.print(client.read());
            }
        }
        // client.flush();
        client.stop(); //acabou a leitura dos dados. Finaliza o client.
        delay(10);
    }
}