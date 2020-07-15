/*
This library has based on: 
https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiTelnetToSerial/WiFiTelnetToSerial.ino
https://github.com/esp8266/Arduino/blob/master/libraries/ArduinoOTA/examples/BasicOTA/BasicOTA.ino
 */

#define MAX_SRV_CLIENTS 2
#include <Telnet.h>

const char* ssid = "your-ssid";
const char* password = "your-password";
const char* hostname = "Telnet-Example";

void setup()
{
  Serial.begin(2000000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.printf("\nConnecting to \"%s\"\n",ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.printf("\nReady! Use \"%s\" or \"", hostname);
  Serial.print(WiFi.localIP());
  Serial.printf("\" to connect\n");
  Telnet.begin(hostname);
}

void loop()
{
  Telnet.handle();
  if (Telnet.available())
  {
    Telnet.printf("I haven't %d, not %u, but %.0f tests to do here\n", 1, 2U, 3.f);
    Telnet.printf("You typed:\"%s\"\n", Telnet.read().c_str());
  }
}