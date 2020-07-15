# Telnet-Example [![Build Status](https://travis-ci.org/JonasGMorsch/ESP8266-Telnet-Wireless-Terminal.svg?branch=master)](https://travis-ci.org/JonasGMorsch/ESP8266-Telnet-Wireless-Terminal)

This library enables you to use a telnet wireless terminal on an ESP8266, it also serves as setup for ArduinoOTA, making debugging/uploading wireless.

<img src="https://github.com/JonasGMorsch/ESP8266-Telnet-Wireless-Terminal/blob/master/documentation/Kitty-Terminal.png" width="75%">

## Installing this Library

https://www.arduino.cc/en/Guide/Libraries

## How to Use: Code

Go to [Example](https://github.com/JonasGMorsch/ESP8266-Telnet-Wireless-Terminal/blob/master/examples/Telnet-Example/Telnet-Example.ino) or:

1 - ```#include <Telnet.h>```

2 - call ```Telnet.begin("your-hostname");``` on setup() **But after WiFi.begin();** 

3 - put ```Telnet.handle();``` on loop()

4 - call ```Telnet.printf();``` to write or ```Telnet.available();``` + ```Telnet.read();``` to read the values from terminal

**Be Aware:**  It takes 6ms+ to read from terminal

## How to Use: Terminal

Run Terminal.cmd, it's configured to answer to host "Telnet-Example", but any phrase on ```Telnet.begin("your-hostname");``` would work, and also the IP address that is given on serial terminal, but since it changes form one network to another i prefer a hostname.

To configure manually use [this guide](https://www.ssh.com/ssh/putty/windows/)

