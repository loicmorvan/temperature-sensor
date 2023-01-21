#include "LM35Sensor.h"
#include <Arduino.h>

#define ADC_VREF_mV    3300.0
#define ADC_RESOLUTION 4096.0

struct LM35Sensor::Pimpl {
    uint8_t pin;
};

LM35Sensor::LM35Sensor(unsigned char pin)
{
    pimpl = new Pimpl();
    pimpl->pin = pin;

    pinMode(pin, INPUT);
}

FloatValue LM35Sensor::GetTemperature()
{
    auto milliVolt = analogRead(pimpl->pin) * (ADC_VREF_mV / ADC_RESOLUTION);
    auto tempC = milliVolt / 10 + 11.5;

    return {
        .HasValue = true,
        .Value = (float)tempC,
    };
}
