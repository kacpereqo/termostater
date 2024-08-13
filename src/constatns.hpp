#pragma once
#include <cstdint>
#include <Arduino.h>

constexpr time_t THERMOMETER_TIMEOU = 1000 * 60;
constexpr float THERMOMETER_THRESHOLD = 5.0f;

// Path: src/constatns.hpp
constexpr float NaN = 9999.0f;

constexpr uint32_t NTP_OFFSET = 60 * 60;     // In seconds
constexpr uint32_t NTP_INTERVAL = 60 * 1000; // In miliseconds
constexpr char NTP_ADDRESS[] = "europe.pool.ntp.org";

// Path: src/thermometer.hpp
constexpr uint8_t SENSOR_PIN = D2;

// Path: src/http.hpp
constexpr char WIFI_SSID[] = "FTTH-1-2.4G-483580_EXT";
constexpr char WIFI_PASS[] = "QyFxdyrD";
constexpr char HTTP_SERVER[] = "http://192.168.5.4:8000";

// Path: src/eeprom.hppw
constexpr uint16_t SSID_ADDRESS = 0;
constexpr uint16_t SSID_SIZE = 32;

constexpr uint16_t PASS_ADDRESS = 32;
constexpr uint16_t PASS_SIZE = 32;
