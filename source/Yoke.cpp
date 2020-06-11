#include "Yoke.h"


Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    motor(PA_14, PA_15)
{
    printf("Yoke object created\r\n");

    handlerTimer.start();

    motor.setSpeed(100.0f);

    //Yoke handler is executed every 10 ms
    eventQueue.call_every(10ms, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically every 10 ms
*/
void Yoke::handler(void)
{
    counter++;
    float dt = 1e-6 * handlerTimer.elapsed_time().count();
    handlerTimer.reset();

    // LED heartbeat
    systemLed = ((counter & 0x68) == 0x68);
}
