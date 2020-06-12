#include "Yoke.h"
#include "Scale.h"

//XXX global variables
float g_ref;
float g_pos;
float g_proportional;
int16_t g_motorSpeed;


Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    motor(PA_14, PA_15),
    positionPot(PA_0),
    yellowPot(PB_0),
    potentiometerP(PA_1)
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
    float referencePosition = scale<float, float>(0.0f, 1.0f, yellowPot.read(), PositionBorder, (1.0f - PositionBorder));
    g_ref = referencePosition;
    float motorPosition = positionPot.read();
    g_pos = motorPosition;
    float positionError = referencePosition - motorPosition;
    float coefficientP = potentiometerP.read();
    float proportional =  5.0f * coefficientP * positionError;
    g_proportional = proportional;

    float PID = proportional;
    
    int16_t motorSpeed = -scale<float, int16_t>(-1.0f, 1.0f, PID, -MaxSpeed, MaxSpeed);
    g_motorSpeed = motorSpeed;

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
        printf("ref=%f  pos=%f  err=%f  cP=%f  P=%f  ms=%d\r\n", referencePosition, motorPosition, positionError, coefficientP, proportional, motorSpeed);
    }
}
