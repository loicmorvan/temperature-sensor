#pragma once

#include "FloatValue.h"

class LM35Sensor
{
private:
    struct Pimpl;
    Pimpl *pimpl;

public:
    LM35Sensor(unsigned char pin);
    float GetTemperature();
};
