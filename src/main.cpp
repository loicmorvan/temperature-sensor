#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>
#include <HomeKitAccessory.h>

#include "credentials.h"

TemperatureSensor *temperatureSensor;
HomeKitAccessory *homeKitAccessory;

// TODO: Cure output.

void setup()
{
	Serial.begin(115200);

	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.println("Establishing connection to WiFi...");
		delay(1000);
	}
	Serial.write("WiFi connected with IP: ");
	Serial.println(WiFi.localIP());

	Serial.println();

	Serial.println("Creating temperature sensor...");
	temperatureSensor = new TemperatureSensor();
	Serial.println("Temperature sensor created.");

	Serial.println();

	Serial.println("Creating HomeKit accessory...");
	homeKitAccessory = new HomeKitAccessory();
	Serial.println("HomeKit accessory created.");

	pinMode(14, INPUT);

	Serial.println("======== Setup finished!");
}

void loop()
{
	if (digitalRead(14) == HIGH)
	{
		Serial.println("Button pushed!");
		homeKitAccessory->ResetPairings();
	}

	Serial.println("=== Loop!");

	auto temperature = temperatureSensor->GetTemperature();
	if (temperature.HasValue)
	{
		Serial.write("Temperature °C: ");
		Serial.println(temperature.Value);
		
		homeKitAccessory->SetTemperature(temperature.Value);
	}
	else
	{
		Serial.println("Temperature sensor is not connected.");
	}

	delay(1000);
}
