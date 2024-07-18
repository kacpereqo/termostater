#pragma once

#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cstdint>
#include "constatns.hpp"

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

class Time
{
private:
  WiFiUDP ntpUDP;
  NTPClient timeClient;

public:
  Time() : timeClient(ntpUDP)
  {
    timeClient.begin();
    timeClient.setTimeOffset(NTP_OFFSET);
    timeClient.setUpdateInterval(NTP_INTERVAL);
  }

  void begin() { timeClient.begin(); }

  unsigned long getEpochTime()
  {
    timeClient.update();
    return timeClient.getEpochTime();
  }
};