#pragma once
#include <cstdint>

class Config
{
private:
    Config();

public:
    static Config &getInstance();

    uint64_t delay;
    float min_threshold_temperature;
    float max_threshold_temperature;
    float target_temperature;
};