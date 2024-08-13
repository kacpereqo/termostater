#include "eeprom.hpp"
#include <EEPROM.h>
#include <cstddef>
#include "constatns.hpp"

Eeprom::Eeprom()
{
    EEPROM.begin(512);

    this->ssid = this->readSsid();
    this->password = this->readPassword();
}

Eeprom::~Eeprom()
{
    delete[] this->ssid;
    delete[] this->password;
}

void Eeprom::write(size_t address, char *data)
{
    const size_t length = strlen(data);

    for (size_t i = 0; i < length; i++)
    {
        EEPROM.write(address + i, data[i]);
    }
    EEPROM.write(address + length, '\0');
    EEPROM.commit();
}

char *Eeprom::read(size_t address, size_t length)
{
    char *buffer = new char[length];
    for (size_t i = 0; i < length; i++)
    {
        buffer[i] = EEPROM.read(address + i);
    }
    return buffer;
}

void Eeprom::writeSsid(char *ssid)
{
    this->write(SSID_ADDRESS, ssid);
}

void Eeprom::writePassword(char *password)
{
    this->write(PASS_ADDRESS, password);
}

char *Eeprom::readSsid()
{
    return this->read(SSID_ADDRESS, SSID_SIZE);
}

char *Eeprom::readPassword()
{
    return this->read(PASS_ADDRESS, PASS_SIZE);
}
