#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "constatns.hpp"
#include "http.hpp"

void HTTP::connect()
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

  void getConfig(Config & config);
}

void HTTP::sendData(float tempereature, char *serialNumber)
{
  HTTPClient http;
  WiFiClient client;
  char url[256];

  sprintf(url, "%s?serial_number=%s&temperature=%f", HTTP_SERVER, serialNumber, tempereature);

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