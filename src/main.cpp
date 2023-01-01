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
		Serial.println("Establishing connection to WiFi..");
		delay(1000);
	}

	temperatureSensor = new TemperatureSensor();
	homeKitAccessory = new HomeKitAccessory();
}

void loop()
{
	auto temperature = temperatureSensor->GetTemperature();
	if (temperature.HasValue)
	{
		//homeKitAccessory->SetTemperature(temperature.Value);
	}
	else
	{
		Serial.println("Temperature sensor is not connected.");
	}

	delay(1000);
}
