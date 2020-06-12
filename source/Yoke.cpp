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

    const float PositionBorder = 0.15f;
    float referencePosition = scale<float, float>(PositionBorder, (1.0f - PositionBorder), yellowPot.read(), 0.0f, 1.0f);
    float motorPosition = positionPot.read();
    float positionError = referencePosition - motorPosition;
    
    int16_t motorSpeed = -scale<float, int16_t>(0.0f, 1.0f, referencePosition, -MaxSpeed, MaxSpeed);

    if((motorPosition < PositionBorder) ||
        (motorPosition > (1.0f - PositionBorder)))
    {
        motor.setSpeed(0.0f);
    }
    else
    {
        motor.setSpeed(motorSpeed);
    }

    if(counter % 100 == 0)
    {
        printf("ref=%f  pos=%f  err=%f\r\n", referencePosition, motorPosition, positionError);
    }
}
