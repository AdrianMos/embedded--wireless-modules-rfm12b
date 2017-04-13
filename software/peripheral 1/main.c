////////////////////////////////PERIFERIC/////////////////////////
#include "OS.h"
#include "data.h"
#include <avr\interrupt.h>

int main()
{ 
    OS_init();
    sei(); //enable global interrupts

    while(1)
    {
        OS_run();
    }

    return(0);
}








