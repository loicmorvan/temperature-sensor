#include <ESP32HomeKit.h>

class HomeKitAccessory {
    private:
        hap_char_t *temperatureCharacteristic;

    public:
        HomeKitAccessory();

        void SetTemperature(const float &value);
};
