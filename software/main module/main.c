//////////////////////////////CENTRAL////////////////////////
#include "local.h"
#include <avr\interrupt.h>
#include "OS.h"
//#include<util/delay.h>

int main()
{ 
    OS_init();

    //ENABLE INTERRUPTS
    sei();             //enable global interrupts

    //SET_BIT(MCUCR,3);  //set the interrupt mode to rising edge
    //SET_BIT(MCUCR,2);
    //SET_BIT(GICR, 7);  //enable external interrupt 1

    /////////////
    //SET_BIT(MCUCR,1);  //set the interrupt mode to FALLING EDGE
    //CLR_BIT(MCUCR,0);
    //SET_BIT(GICR, 6);  //enable external interrupt 0
    ///////////////////

    //enable interrupt on match      --   Timer/Counter Interrupt Mask
    SET_BIT(TIMSK, 7);       
    TCCR2=0x0F;
    OCR2 = 25;    

    while(1)
    {
        OS_run();
    }

    return(0);   
}


/*
ISR(INT0_vect) 
{

}
*/












