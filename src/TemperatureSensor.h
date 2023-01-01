#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 2

struct FloatValue {
    bool HasValue;
    float Value;
};

class TemperatureSensor {
    private:
        OneWire* oneWire;
        DS18B20* sensor;

    public:
        TemperatureSensor();
        FloatValue GetTemperature();
};
