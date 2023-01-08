#pragma once

#include "FloatValue.h"

class TemperatureSensor
{
private:
    struct Pimpl;
    Pimpl *pimpl;

public:
    TemperatureSensor();
    FloatValue GetTemperature();
};
