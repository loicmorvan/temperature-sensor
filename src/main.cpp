#include <Arduino.h>
#include <TemperatureSensor.h>
#include <WiFi.h>

#include "credentials.h"

TemperatureSensor *temperatureSensor;
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
}

void loop()
{
	temperatureSensor->WaitForData();
	delay(1000);
}
