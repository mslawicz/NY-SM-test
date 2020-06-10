#include "Yoke.h"
#include <mbed.h>


int main()
{
    printf("Nucleo Yoke SM (test)\r\n");

    // main event queue
    events::EventQueue eventQueue;

    // create Yoke object
    Yoke yoke(eventQueue);

    // process the event queue
    eventQueue.dispatch_forever();

    return 0;
}

