#include <Arduino.h>
#include <TemperatureSensor.h>

TemperatureSensor* temperatureSensor;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  temperatureSensor = new TemperatureSensor();
}

void loop()
{
  temperatureSensor->WaitForData();
  delay(1000);
}
