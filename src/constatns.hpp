#pragma once
#include <cstdint>

constexpr char URL[] = "http:/";

// Path: src/constatns.hpp
constexpr uint32_t NTP_OFFSET = 60 * 60;     // In seconds
constexpr uint32_t NTP_INTERVAL = 60 * 1000; // In miliseconds
constexpr char NTP_ADDRESS[] = "europe.pool.ntp.org";

// Path: src/http.hpp
constexpr char WIFI_SSID[] = "FTTH-1-2.4G-483580_EXT";
constexpr char WIFI_PASS[] = "QyFxdyrD";
constexpr char HTTP_SERVER[] = "http://192.168.5.6:8000/reading";