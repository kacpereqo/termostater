#pragma once
#include <DallasTemperature.h>
#include <OneWire.h>
#include <array>
#include <cstdint>
#include <sys/types.h>
#include "constatns.hpp"

constexpr uint8_t PIN = D2;

class Thermometer
{
private:
  OneWire oneWire;
  DallasTemperature sensors;

  char *getSerialNumber()
  {
    DeviceAddress deviceAddress;
    this->sensors.getAddress(deviceAddress, 0);
    char *serialNumber = new char[17];
    for (size_t i = 0; i < 8; i++)
    {
      sprintf(serialNumber + i * 2, "%02X", deviceAddress[i]);
    }
    serialNumber[16] = '\0';
    return serialNumber;
  }

public:
  char *serialNumber;

  Thermometer()
  {
    this->oneWire = OneWire(PIN);
    this->sensors = DallasTemperature(&oneWire);
    sensors.begin();
    sensors.setResolution(12);
    this->serialNumber = getSerialNumber();
  }

  float getTemperature()
  {
    this->sensors.requestTemperatures();
    return this->sensors.getTempCByIndex(0);
  }
};
