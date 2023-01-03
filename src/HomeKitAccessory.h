#include <ESP32HomeKit.h>

class HomeKitAccessory
{
private:
    hap_char_t *temperatureCharacteristic;

public:
    HomeKitAccessory();

    void SetTemperature(const float &value);

private:
    hap_serv_t *create_temperature_service();
    hap_acc_t *create_accessory();
};
