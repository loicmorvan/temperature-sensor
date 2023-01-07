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
stateDiagram-v2
    state "Connecting WiFi" as wifi
    state "Creating software temperature sensor" as temp
    state "Creating HomeKit accessory" as home
    state "Setup" as setup
    state "Loop" as loop
    state "Handle button state" as button
    state "Get temperature from sensor" as get
    state "Set temperature to accessory" as set
    state "Wait for 10 seconds" as wait
    state "Try detecting hardware sensor" as try

    state setup {
        [*] --> wifi
        wifi --> temp: WiFi connected
        wifi --> [*]: WiFi not connected
        temp --> home: Temperature sensor created
        home --> [*]: HomeKit accessory created
    }

    state temp {
        [*] --> try
        try --> try: Sensor not found
        try --> [*]: Sensor found
    }

    state loop {
        [*] --> button
        button --> get: No button pressed
        button --> [*]: Button pressed
        get --> set: Temperature received
        get --> wait: Temperature not received
        set --> wait: Temperature sent
        wait --> button: Delay finished
    }

    [*] --> setup
    setup --> loop: setup successful
    loop --> [*]: reset button pressed
    setup --> [*]: setup failed
```
