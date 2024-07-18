#pragma once

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "constatns.hpp"

class HTTP
{
public:
  void connect();
  void sendData(float tempereature, char *serialNumber, time_t epochTime);
};