#pragma once
#include <DallasTemperature.h>
#include <OneWire.h>
#include <array>
#include <cstdint>
#include <sys/types.h>

constexpr uint8_t PIN = D2;

class Thermometer {
private:
  OneWire oneWire;
  DallasTemperature sensors;

public:
  Thermometer() {
    this->oneWire = OneWire(PIN);
    this->sensors = DallasTemperature(&oneWire);
    sensors.begin();
    sensors.setResolution(12);
  }

  char *getSerialNumber() {
    std::array<uint8_t, 17> serialNumber;
    sensors.getAddress(serialNumber.data(), 0);
    static char serialNumberStr[17 * 2 + 1];
    for (size_t i = 0; i < 8; i++) {
      sprintf(&serialNumberStr[i * 2], "%02X", serialNumber[i]);
    }
    return serialNumberStr;
  }

  float getTemperature() {
    this->sensors.requestTemperatures();
    return this->sensors.getTempCByIndex(0);
  }
};
