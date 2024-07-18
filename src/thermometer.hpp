#pragma once
#include <DallasTemperature.h>
#include <OneWire.h>

class Thermometer
{
private:
  OneWire oneWire;
  DallasTemperature sensors;

  char *getSerialNumber();

public:
  char *serialNumber;

  Thermometer();

  float getTemperature();
};
