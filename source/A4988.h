#ifndef A4988_H_
#define A4988_H_

#include <mbed.h>

class A4988
{
public:
    A4988(PinName directionPin, PinName stepPin);
private:
    DigitalOut direction;
    PwmOut step;
};

#endif /* A4988_H_ */