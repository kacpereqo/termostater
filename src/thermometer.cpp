#include "thermometer.hpp"
#include "constatns.hpp"

char *Thermometer::getSerialNumber()
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

Thermometer::Thermometer()
{
    this->oneWire = OneWire(SENSOR_PIN);
    this->sensors = DallasTemperature(&oneWire);
    sensors.begin();
    sensors.setResolution(12);
    this->serialNumber = getSerialNumber();
}

float Thermometer::getTemperature()
{
    this->sensors.requestTemperatures();
    return this->sensors.getTempCByIndex(0);
}