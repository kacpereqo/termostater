#pragma once

#include <cstddef>

class Eeprom
{
private:
    void write(size_t address, char *data);
    char *read(size_t address, size_t length);

    char *readSsid();
    char *readPassword();

public:
    char *ssid;
    char *password;

    Eeprom();
    ~Eeprom();

    void begin();
    void writeSsid(char *ssid);
    void writePassword(char *password);
};