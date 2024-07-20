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
  void connect();
  void getConfig(Config &config);
  void sendData(float tempereature, char *serialNumber);
};