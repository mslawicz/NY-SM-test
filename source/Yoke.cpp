#include "Yoke.h"
#include "Scale.h"


Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    motor(PA_14, PA_15),
    positionPot(PA_0),
    yellowPot(PB_0)
{
    printf("Yoke object created\r\n");

    handlerTimer.start();

    //Yoke handler is executed every 10 ms
    eventQueue.call_every(10ms, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically every 10 ms
*/
void Yoke::handler(void)
{
    const int16_t MaxSpeed = 14500;
    counter++;
    float dt = 1e-6 * handlerTimer.elapsed_time().count();
    handlerTimer.reset();

    // LED heartbeat
    systemLed = ((counter & 0x68) == 0x68);

    float yellowPotValue = yellowPot.read();
    float position = positionPot.read();
    int16_t motorSpeed = -scale<float, int16_t>(0.0f, 1.0f, yellowPotValue, -MaxSpeed, MaxSpeed);
    //motor.setSpeed(motorSpeed);

    if(counter % 100 == 0)
    {
        printf("pos=%f  %d\r\n", position, motorSpeed);
    }
}
