#include "TemperatureSensor.h"

#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 32

struct TemperatureSensor::Pimpl
{
    OneWire *oneWire;
    DS18B20 *sensor;
};

TemperatureSensor::TemperatureSensor()
{
    pimpl = new Pimpl();

    pimpl->oneWire = new OneWire(ONE_WIRE_BUS);
    pimpl->sensor = new DS18B20(pimpl->oneWire);

    // wait until address found
    if (pimpl->sensor->begin() == false)
    {
        while (!pimpl->sensor->begin())
            ; // wait until device comes available.
    }

    pimpl->sensor->setResolution(9);
    pimpl->sensor->setConfig(DS18B20_CRC);
    pimpl->sensor->requestTemperatures();
}

FloatValue TemperatureSensor::GetTemperature()
{
    pimpl->sensor->requestTemperatures();

    uint32_t timeout = millis();
    while (!pimpl->sensor->isConversionComplete())
    {
        if (millis() - timeout >= 800) // check for timeout
        {
            Serial.println("ERROR: timeout or disconnect");
            return {
                .HasValue = false,
            };
        }
    }

    return {
        .HasValue = true,
        .Value = pimpl->sensor->getTempC(),
    };
}
