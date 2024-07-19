#include <Arduino.h>

#include "http.hpp"
#include "thermometer.hpp"
#include "time.hpp"
#include "eeprom.hpp"

HTTP httpClient;
Time dateTime;
Thermometer thermometer;
Eeprom eeprom;

void setup()
{

  Serial.begin(9600);
  while (!Serial)
    ;
  eeprom.begin();
  httpClient.connect();
  dateTime.begin();
}

void loop()
{
  float temperature = thermometer.getTemperature();
  char *serialNumber = thermometer.serialNumber;
  time_t epochTime = dateTime.getEpochTime();

  httpClient.sendData(temperature, serialNumber, epochTime);

  delay(1000);
}