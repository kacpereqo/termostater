#pragma once

#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class HTTP {
public:
  void connect() {
    Serial.println("HTTP client initialized");

    constexpr char WIFI_SSID[] = "FTTH-1-2.4G-483580_EXT";
    constexpr char WIFI_PASS[] = "QyFxdyrD";

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.println();
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("success!");
    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());
  }
};