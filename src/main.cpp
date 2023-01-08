#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>
#include <HomeKitAccessory.h>
#include <Dispatcher.h>
#include <ButtonController.h>
#include <TricolorController.h>

#include "credentials.h"

Dispatcher *dispatcher;
unsigned long lastTime;

void setup()
{
	auto tricolorController = new TricolorController();
	tricolorController->SetColor(0, 0, 255);

	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
	}

	tricolorController->SetColor(0, 255, 255);

	auto temperatureSensor = new TemperatureSensor();
	auto homeKitAccessory = new HomeKitAccessory();
	auto buttonController = new ButtonController();

	dispatcher = new Dispatcher();

	dispatcher->StartTimer(TimeSpan::FromSeconds(10), [=]()
						   {
		auto temperature = temperatureSensor->GetTemperature();
		if (temperature.HasValue)
		{
			tricolorController->SetColor(0, 0, 0);
			homeKitAccessory->SetTemperature(temperature.Value);
		}
		else
		{
			tricolorController->SetColor(255, 0, 0);
			// Temperature sensor lost
		} });

	dispatcher->StartTimer(TimeSpan::FromMilliseconds(100), [=]()
						   {
		if (buttonController->IsButtonPressed())
		{
			tricolorController->SetColor(255, 255, 0);
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
