#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor()
{
    oneWire = new OneWire(ONE_WIRE_BUS);
    sensor = new DS18B20(oneWire);

    // wait until address found
    if (sensor->begin() == false)
    {
        while (!sensor->begin())
            ; // wait until device comes available.
    }

    sensor->setResolution(12);
    sensor->setConfig(DS18B20_CRC);
    sensor->requestTemperatures();
}

FloatValue TemperatureSensor::GetTemperature()
{
    sensor->requestTemperatures();

    uint32_t timeout = millis();
    while (!sensor->isConversionComplete())
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
        .Value = sensor->getTempC(),
    };
}
