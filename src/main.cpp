#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>
#include <HomeKitAccessory.h>
#include <Dispatcher.h>

#include "credentials.h"

TemperatureSensor *temperatureSensor;
HomeKitAccessory *homeKitAccessory;
Dispatcher *dispatcher;
unsigned long lastTime;

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

	dispatcher = new Dispatcher();
	dispatcher->StartTimer(TimeSpan::FromSeconds(10), [](){
		auto temperature = temperatureSensor->GetTemperature();
		if (temperature.HasValue)
		{
			homeKitAccessory->SetTemperature(temperature.Value);
		}
		else
		{
			// Temperature sensor lost
		}
	});
	dispatcher->StartTimer(TimeSpan::FromSeconds(1), [](){
		Serial.println("time 1s");
	});
	dispatcher->StartTimer(TimeSpan::FromSeconds(5), [](){
		Serial.println("time 5s");
	});
}

void loop()
{
	auto currentTime = millis();
	dispatcher->Execute(TimeSpan::FromMilliseconds(lastTime - currentTime));
	lastTime = currentTime;

	if (digitalRead(14) == HIGH)
	{
		homeKitAccessory->ResetPairings();
	}

	delay(100);
}
