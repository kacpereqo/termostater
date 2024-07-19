#pragma once
#include <cstdint>
#include <Arduino.h>

constexpr char URL[] = "http:/";

// Path: src/constatns.hpp
constexpr uint32_t NTP_OFFSET = 60 * 60;     // In seconds
constexpr uint32_t NTP_INTERVAL = 60 * 1000; // In miliseconds
constexpr char NTP_ADDRESS[] = "europe.pool.ntp.org";

// Path: src/thermometer.hpp
constexpr uint8_t SENSOR_PIN = D2;

// Path: src/http.hpp
constexpr char WIFI_SSID[] = "FTTH-1-2.4G-483580_EXT";
constexpr char WIFI_PASS[] = "QyFxdyrD";
constexpr char HTTP_SERVER[] = "http://192.168.5.8:8000/reading";

// Path: src/eeprom.hpp
constexpr uint16_t SSID_ADDRESS = 0;
constexpr uint16_t SSID_SIZE = 32;

constexpr uint16_t PASS_ADDRESS = 32;
constexpr uint16_t PASS_SIZE = 32;
