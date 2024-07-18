#pragma once

#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <cstdint>

constexpr uint32_t NTP_OFFSET = 60 * 60;     // In seconds
constexpr uint32_t NTP_INTERVAL = 60 * 1000; // In miliseconds
constexpr char NTP_ADDRESS[] = "europe.pool.ntp.org";

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

class Time {
private:
  WiFiUDP ntpUDP;
  NTPClient timeClient;

public:
  Time() : timeClient(ntpUDP) {
    timeClient.begin();
    timeClient.setTimeOffset(NTP_OFFSET);
    timeClient.setUpdateInterval(NTP_INTERVAL);
  }

  void begin() { timeClient.begin(); }

  unsigned long getEpochTime() {
    timeClient.update();
    return timeClient.getEpochTime();
  }
};