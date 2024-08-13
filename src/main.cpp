#include <Arduino.h>

#include "http.hpp"
#include "thermometer.hpp"
#include "eeprom.hpp"
#include "constatns.hpp"

enum class State
{
  Normal,
  Config,
  Error
};

void setup()
{

  HTTP httpClient;
  Thermometer thermometer;
  Eeprom eeprom;
  State state = State::Normal;

  Serial.begin(9600);
  while (!Serial)
    ;

  httpClient.getConfig(thermometer.serialNumber);

  Config &config = Config::getInstance();

  Serial.println("Starting loop");

  if (config.target_temperature == NaN or config.min_threshold_temperature == NaN or config.max_threshold_temperature == NaN)
    state = State::Config;

  if (state == State::Config)
  {
    float lastTemperature = thermometer.getTemperature();
    float lastUpdate = millis();

    while (true)
    {
      float currentTemperature = thermometer.getTemperature();
      time_t currentTime = millis();

      if (currentTime - lastUpdate < THERMOMETER_TIMEOU)
      {
        config.target_temperature = currentTemperature;
        config.min_threshold_temperature = currentTemperature - THERMOMETER_THRESHOLD;
        config.max_threshold_temperature = currentTemperature + THERMOMETER_THRESHOLD;
        httpClient.sendConfig(thermometer.serialNumber);
      }

      httpClient.sendData(currentTemperature, thermometer.serialNumber);
      if (lastTemperature < currentTemperature)
      {
        lastTemperature = currentTemperature;
        lastUpdate = currentTime;
      }
      delay(1000);
    }
  }
  // else if (state == State::Normal)
  // {
  //   float currentTemperature = thermometer.getTemperature();
  //   httpClient.sendData(currentTemperature, thermometer.serialNumber);
  // }
}

void loop()
{
}