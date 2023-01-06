class HomeKitAccessory
{
private:
    class Pimpl;
    Pimpl *pimpl;

public:
    HomeKitAccessory();

    void SetTemperature(const float &value);
    void ResetPairings() const;
};
