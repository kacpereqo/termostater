#pragma once

#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cstdint>

class Time
{
private:
  WiFiUDP ntpUDP;
  NTPClient timeClient;

public:
  Time();

  void begin();

  time_t getEpochTime();
};