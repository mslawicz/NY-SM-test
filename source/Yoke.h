#ifndef YOKE_H_
#define YOKE_H_

#include <mbed.h>
#include "A4988.h"

class Yoke
{
public:
    Yoke(events::EventQueue& eventQueue);
private:
    void handler(void);
    events::EventQueue& eventQueue;     // event queue of the main thread
    DigitalOut systemLed;               // yoke heartbeat LED
    uint32_t counter{0};                // counter of handler execution
    Timer handlerTimer;                 // measures time between handler calls
    A4988 motor;                        // stepper motor under test
    AnalogIn positionPot;               // motor position potentiometer
    AnalogIn yellowPot;                 // potentiometer with yellow knob
    AnalogIn potentiometerP;            // PID P potentiometer
};

#endif /* YOKE_H_ */