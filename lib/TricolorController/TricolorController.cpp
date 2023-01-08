#include "TricolorController.h"

#include <Arduino.h>

TricolorController::TricolorController()
{
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
}

void TricolorController::SetColor(char r, char g, char b)
{
    analogWrite(25, r);
    analogWrite(26, g);
    analogWrite(27, b);
}
