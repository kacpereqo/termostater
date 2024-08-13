#include "config.hpp"

Config &Config::getInstance()
{
    static Config instance;
    return instance;
}

Config::Config()
{
    this->delay = 10000;
    this->target_temperature = 25.0;
    this->min_threshold_temperature = 20.0;
    this->max_threshold_temperature = 30.0;
}