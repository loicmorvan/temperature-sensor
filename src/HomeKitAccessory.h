#include <ESP32HomeKit.h> // TODO: Avoid including HomeKit everywhere this class is used.

class HomeKitAccessory
{
private:
    hap_serv_t *service;

public:
    HomeKitAccessory();

    void SetTemperature(const float &value);
    void ResetPairings() const;

private:
    hap_serv_t *create_temperature_service();
    hap_acc_t *create_accessory();
};
