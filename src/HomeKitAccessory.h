class HomeKitAccessory {
    public:
        HomeKitAccessory();

        bool IsConnected() const;
        void SetTemperature(const float &value);
};
