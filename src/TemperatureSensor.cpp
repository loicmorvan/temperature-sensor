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

void TemperatureSensor::WaitForData()
{
    auto start = millis();
    sensor->requestTemperatures();

    // wait for data AND detect disconnect
    uint32_t timeout = millis();
    while (!sensor->isConversionComplete())
    {
        if (millis() - timeout >= 800) // check for timeout
        {
            Serial.println("ERROR: timeout or disconnect");
            break;
        }
    }

    float t = sensor->getTempC();

    if (t == DEVICE_CRC_ERROR)
    {
        Serial.println("ERROR: CRC error");
    }
    auto stop = millis();

    Serial.print(12);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(t, 1); // 1 decimal makes perfect sense
}