Temperature sensor
==================

This temperature sensor measure the temperature and publishes it as a HomeKit accessory. A button is provided to reset the connections to existing controllers (like an iPhone or a HomeKit concentrator).

This temperature sensor uses these components:
- ESP32-DevKitM-1.
- DS18B20.
- A resistor.
- A button.

![Temperature sensor schema](./docs/Schematic_TemperatureSensor_2023-01-06.png)

## States

```mermaid
---
title: State machine of the temperature sensor
---
stateDiagram-v2
    state Booting {
        [*] --> ConnectingWiFi
        ConnectingWiFi --> CreatingTemperatureSensor: WiFi connected
        ConnectingWiFi --> [*]: WiFi not connected
        CreatingTemperatureSensor --> CreatingHomeKitAccessory: Temperature sensor created
        CreatingTemperatureSensor --> [*]: Temperature sensor error
        CreatingHomeKitAccessory --> [*]: HomeKit accessory created
    }
    state Running {
        [*] --> HandleButton
        HandleButton --> GetTemperature: No button pressed
        HandleButton --> [*]: Button pressed
        GetTemperature --> SetTemperature: Temperature received
        GetTemperature --> Wait: Temperature not received
        SetTemperature --> Wait
        Wait --> GetTemperature
    }

    [*] --> Booting
    Booting --> Running: boot successful
    Running --> [*]: reset button pressed
    Booting --> [*]: boot failed
```

- Booting: the temperature sensor tries to connect to the WiFi, then creates the driver for the DS18B20 sensor and declares the accessory to the HomeKit system.
- Running: Reads the state of the _reset button_, read the temperature and publishes the value to the HomeKit accessory.
