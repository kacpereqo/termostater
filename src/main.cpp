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

  Serial.begin(9600);
  while (!Serial)
    ;

  HTTP httpClient;
  Thermometer thermometer;
  Eeprom eeprom;
  State state = State::Normal;

  httpClient.getConfig(thermometer.serialNumber);

  Config &config = Config::getInstance();

  Serial.println("Starting loop");

  Serial.println(config.target_temperature);
  Serial.println(config.min_threshold_temperature);
  Serial.println(config.max_threshold_temperature);

  if (config.target_temperature == NaN or config.min_threshold_temperature == NaN or config.max_threshold_temperature == NaN)
  {
    state = State::Config;
    Serial.println("Config");
  }

  while (true)
  {
    if (state == State::Config)
    {

      float lastTemperature = thermometer.getTemperature();
      float lastUpdate = millis();

      while (true)
      {
        float currentTemperature = thermometer.getTemperature();
        time_t currentTime = millis();

        Serial.print("Target temperature: ");
        Serial.print(config.target_temperature);
        Serial.print(" lastUpdate: ");
        Serial.println(lastUpdate - millis());

        if (currentTime - lastUpdate > THERMOMETER_TIMEOU)
        {
          config.target_temperature = currentTemperature;
          config.min_threshold_temperature = currentTemperature - THERMOMETER_THRESHOLD;
          config.max_threshold_temperature = currentTemperature + THERMOMETER_THRESHOLD;
          httpClient.sendConfig(thermometer.serialNumber, config);
          Serial.println("config");
          state = State::Normal;
          break;
        }

        httpClient.sendData(currentTemperature, thermometer.serialNumber);
        Serial.println(abs(currentTemperature - lastTemperature));
        if (abs(currentTemperature - lastTemperature) > 0.5f)
        {
          lastTemperature = currentTemperature;
          lastUpdate = currentTime;
        }
        delay(1000);
      }
    }

    else if (state == State::Error)
    {
      Serial.println("Error");
    }
    else if (state == State::Normal)
    {
      Serial.println("Normal");
      float currentTemperature = thermometer.getTemperature();
      httpClient.sendData(currentTemperature, thermometer.serialNumber);
    }
  }
}

void loop()
{
}