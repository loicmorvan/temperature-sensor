#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>
#include <HomeKitAccessory.h>
#include <Dispatcher.h>
#include <ButtonController.h>

#include "credentials.h"

Dispatcher *dispatcher;
unsigned long lastTime;

void setup()
{
	Serial.begin(115200);
	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
	}

	auto temperatureSensor = new TemperatureSensor();
	auto homeKitAccessory = new HomeKitAccessory();

	auto buttonController = new ButtonController();

	dispatcher = new Dispatcher();
	dispatcher->StartTimer(TimeSpan::FromSeconds(10), [=]()
						   {
		auto temperature = temperatureSensor->GetTemperature();
		if (temperature.HasValue)
		{
			homeKitAccessory->SetTemperature(temperature.Value);
		}
		else
		{
			// Temperature sensor lost
		} });
	dispatcher->StartTimer(TimeSpan::FromMilliseconds(100), [=]()
						   {
		if (buttonController->IsButtonPressed())
		{
			homeKitAccessory->ResetPairings();
		} });
}

void loop()
{
	auto currentTime = millis();
	dispatcher->Execute(TimeSpan::FromMilliseconds(currentTime - lastTime));
	lastTime = currentTime;

	delay(100);
}
