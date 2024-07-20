#pragma once
#include <cstdint>

class Config
{
private:
    Config();

public:
    Config &getInstance();

    uint64_t delay;
    float min_threshold_temperature;
    float max_threshold_temperature;
};