#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor()
{
    Serial.print("DS18B20 Library version: ");
    Serial.println(DS18B20_LIB_VERSION);

    oneWire = new OneWire(ONE_WIRE_BUS);
    sensor = new DS18B20(oneWire);

    // wait until address found
    if (sensor->begin() == false)
    {
        Serial.println("ERROR: No device found");
        while (!sensor->begin())
            ; // wait until device comes available.
    }

    sensor->setResolution(12);
    sensor->setConfig(DS18B20_CRC); // or 1
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
                .HasValue = false};
        }
    }

    return {
        .HasValue = true,
        .Value = sensor->getTempC()};
}
