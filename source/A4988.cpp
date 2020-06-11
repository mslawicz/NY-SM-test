#include "A4988.h"

A4988::A4988(PinName directionPin, PinName stepPin) :
    direction(directionPin),
    step(stepPin)
{
    step.write(0.0f);
}

void A4988::setSpeed(int16_t pulseFrequency)
{
    if(pulseFrequency == 0)
    {
        step.write(0.0f);
    }
    else
    {
        direction = pulseFrequency >= 0 ? 0 : 1;
        step.write(0.5f);
        step.period(1.0f / abs(pulseFrequency));
    }
}