#include <Arduino.h>

#include "http.hpp"
// #include "thermometer.hpp"

constexpr char WIFI_SSID[] = "FTTH-1-2.4G-483580_EXT";
constexpr char WIFI_PASS[] = "QyFxdyrD";

HTTP httpClient;
// Time dateTime;
// Thermometer thermometer;

void setup() {

  Serial.begin(9600);
  while (!Serial)
    ;
  // httpClient.connect();
  // dateTime.begin();
}

void loop() {

  // Serial.println(dateTime.getEpochTime());
  // Serial.println(thermometer.getTemperature());

  delay(1000);
}