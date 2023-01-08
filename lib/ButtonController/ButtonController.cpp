#include "ButtonController.h"

#include <Arduino.h>

ButtonController::ButtonController()
{
    pinMode(14, INPUT);
}

bool ButtonController::IsButtonPressed()
{
    return digitalRead(14) == HIGH;
}
