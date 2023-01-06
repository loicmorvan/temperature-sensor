#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>
#include <HomeKitAccessory.h>

#include "credentials.h"

TemperatureSensor *temperatureSensor;
HomeKitAccessory *homeKitAccessory;

void setup()
{
	Serial.begin(115200);

	WiFi.begin(SSID, PASSWORD);
	Serial.write("Establishing connection to WiFi...");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.write('.');
	}
	Serial.println("connected!");

	temperatureSensor = new TemperatureSensor();
	homeKitAccessory = new HomeKitAccessory();

	pinMode(14, INPUT);
}

void loop()
{
	if (digitalRead(14) == HIGH)
	{
		homeKitAccessory->ResetPairings();
	}

	auto temperature = temperatureSensor->GetTemperature();
	if (temperature.HasValue)
	{
		homeKitAccessory->SetTemperature(temperature.Value);
	}
	else
	{
		// Temperature sensor lost
	}

	// Wait for 10s, need to find a way to check temperature at 0.1Hz,
	// but still listen for the button at a higher framerate.
	delay(10000);
}
