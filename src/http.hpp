#pragma once

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "constatns.hpp"
#include "config.hpp"

class HTTP
{
public:
  HTTP();
  void getConfig(char *serial_number);
  void sendConfig(char *serial_number, Config &config);
  void sendData(float tempereature, char *serialNumber);
};