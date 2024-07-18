#pragma once

#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cstdint>
#include "constatns.hpp"
#include "time.hpp"

Time::Time() : timeClient(ntpUDP)
{
  timeClient.begin();
  timeClient.setTimeOffset(NTP_OFFSET);
  timeClient.setUpdateInterval(NTP_INTERVAL);
}

void Time::begin() { timeClient.begin(); }

time_t Time::getEpochTime()
{
  timeClient.update();
  return timeClient.getEpochTime();
}