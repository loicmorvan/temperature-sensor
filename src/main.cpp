#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>
#include <HomeKitAccessory.h>

#include "credentials.h"

TemperatureSensor *temperatureSensor;
HomeKitAccessory *homeKitAccessory;
uint32_t start, stop;

void setup()
{
	Serial.begin(115200);

	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.println("Establishing connection to WiFi..");
	}

	temperatureSensor = new TemperatureSensor();
	homeKitAccessory = new HomeKitAccessory();
}

void loop()
{
	auto temperature = temperatureSensor->GetTemperature();
	if (temperature.HasValue)
	{
		if (homeKitAccessory->IsConnected())
		{
			homeKitAccessory->SetTemperature(temperature.Value);
		}
		else
		{
			Serial.write("HomeKit accessory is not connected.");
		}
	}
	else
	{
		Serial.write("Temperature sensor is not connected.");
	}

	delay(1000);
}
