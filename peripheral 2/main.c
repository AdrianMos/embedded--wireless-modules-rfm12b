////////////////////////////////PERIFERIC/////////////////////////
#include "OS.h"
#include "data.h"

#include <avr\interrupt.h>

int main()
{ 
    OS_init();

    //enable global interrupts
    sei();             

    ////////////ADC initializare//////////////
    ADMUX  = 0x47;  //0100 0111  - external reference, allign result right, ADC7 single input
    ADCSRA = 0x86;  //1000 0110  - enable ADC, interrupt disable, clock prescaler = 64
    
    while(1)
    {
        OS_run();
    }

    return(0);
}








