#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "constatns.hpp"
#include "http.hpp"
#include "config.hpp"
#include <ArduinoJson.h>

HTTP::HTTP()
{
  Serial.println("HTTP client initialized");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}

void HTTP::sendConfig(char *serial_number, Config &config)
{
  HTTPClient http;
  WiFiClient client;
  char url[256];

  sprintf(url, "%s/config/%s?delay=%lld&min_threshold_temperature=%f&max_threshold_temperature=%f&target_temperature=%f", HTTP_SERVER, serial_number, config.delay, config.min_threshold_temperature, config.max_threshold_temperature, config.target_temperature);

  bool a = http.begin(client, url);
  Serial.println(a);
  int httpCode = http.POST("");

  if (httpCode > 0)
  {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
}

void HTTP::sendData(float tempereature, char *serialNumber)
{
  HTTPClient http;
  WiFiClient client;
  char url[256];

  sprintf(url, "%s/reading?serial_number=%s&temperature=%f", HTTP_SERVER, serialNumber, tempereature);

  bool a = http.begin(client, url);
  Serial.println(a);
  int httpCode = http.POST("");

  if (httpCode > 0)
  {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
}

void HTTP::getConfig(char *serial_number)
{
  Config &config = Config::getInstance();

  HTTPClient http;
  WiFiClient client;
  char url[256];

  sprintf(url, "%s/config/%s", HTTP_SERVER, serial_number);

  bool a = http.begin(client, url);
  Serial.println(a);
  int httpCode = http.GET();

  if (httpCode > 0)
  {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();

      JsonDocument doc;

      DeserializationError error = deserializeJson(doc, payload);
      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        http.end();
        return;
      }

      Serial.println("Deserialized JSON object");

      config.delay = doc["delay"].isNull() ? NaN : doc["delay"].as<int>();
      config.target_temperature = doc["target_temperature"].isNull() ? NaN : doc["target_temperature"].as<float>();
      config.max_threshold_temperature = doc["max_threshold_temperature"].isNull() ? NaN : doc["max_threshold_temperature"].as<float>();
      config.min_threshold_temperature = doc["min_threshold_temperature"].isNull() ? NaN : doc["min_threshold_temperature"].as<float>();
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}