#ifndef TELNET_H
#define TELNET_H

#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <PolledTimeout.h>

#ifndef MAX_SRV_CLIENTS
#define MAX_SRV_CLIENTS 1
#endif

class Telnet
{
  public:
    Telnet() : _telnet(23), _telnetClients(), _ticker()
    {
      _telnet.begin();
      _telnet.setNoDelay(true);
    }

    void begin (const char *hostname)
    {
      ArduinoOTA.setHostname(hostname);
      ArduinoOTA.begin(true);
    }

    void printf(const char *fmt, ...)
    {
      va_list va;
      va_start(va, fmt);
      char buffer[vsnprintf(NULL, 0, fmt, va) + 1];
      vsprintf(buffer, fmt, va);
      va_end(va);

      for (uint8_t i = 0; i < MAX_SRV_CLIENTS; i++)
        _telnetClients[i].write(buffer);
    }

    bool available ()
    {
      for (uint8_t i = 0; i < MAX_SRV_CLIENTS; i++)
        if ( _telnetClients[i].available())
          return 1;
      return 0;
    }

    String read ()
    {
      delay(5); // Give some time for the wifi to stream
      
      String s;
      for (uint8_t i = 0; i < MAX_SRV_CLIENTS; i++)
        while (_telnetClients[i].available())
          s += (char)_telnetClients[i].read();

      if (s != "")
        s.remove(s.length() - 2, 2); // every receved string has caracters 0xA0 and 0x0D at the end

      if (s.equals("reboot"))
      {
        this->printf("Restarting ESP!\n");
        delay(1000);
        ESP.restart();
      }

      return s;
    }

    void handle ()
    {
      esp8266::polledTimeout::periodic static client_timer(1000);

      if (client_timer)
      {
        ArduinoOTA.handle();
        if (_telnet.hasClient()) //check if there are any new clients
        {
          uint8_t i;
          for (i = 0; i < MAX_SRV_CLIENTS; i++) //find free/disconnected spot
            if (!_telnetClients[i])  // equivalent to !telnetClients[i].connected()
            {
              _telnetClients[i] = _telnet.available();
              char buf[50];
              sprintf(buf, "Welcome! You are Client %d of %d \n", i + 1, MAX_SRV_CLIENTS);
              _telnetClients[i].write(buf);
              this->read(); //ignore first string
              break;
            }
          if (i == MAX_SRV_CLIENTS) //no free/disconnected spot so reject
            _telnet.available().println("Max Number of Clients Reached");
        }
      }
    }

  private:

    WiFiServer _telnet;
    WiFiClient _telnetClients[MAX_SRV_CLIENTS];
    Ticker _ticker;
};

Telnet Telnet;
#endif //TELNET_H
