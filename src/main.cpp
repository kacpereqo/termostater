#include <Arduino.h>

#include "http.hpp"
#include "thermometer.hpp"
#include "eeprom.hpp"

HTTP httpClient;
Thermometer thermometer;
Eeprom eeprom;

void setup()
{

  Serial.begin(9600);
  while (!Serial)
    ;
  eeprom.begin();
  httpClient.connect();
}

void loop()
{
  float temperature = thermometer.getTemperature();
  char *serialNumber = thermometer.serialNumber;

  httpClient.sendData(temperature, serialNumber);
}