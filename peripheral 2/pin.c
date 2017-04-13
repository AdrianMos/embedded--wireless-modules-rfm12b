#include "local.h"

void PIN_init()
{
    ///////////////////////////////////////////de corectat///////// !!!!!!!!!!!!!!
    CLR_BIT(DDRD, 3);   //INPUT
    CLR_BIT(PORTD, 3) ; //pull-up disabled

    CLR_BIT(DDRD, 4);   //INPUT
    CLR_BIT(PORTD, 4) ; //pull-up disabled

    CLR_BIT(DDRD, 6);   //INPUT
    CLR_BIT(PORTD, 6) ; //pull-up disabled

    CLR_BIT(DDRC, 5);   //INPUT
    CLR_BIT(PORTC, 5) ; //pull-up disabled

    SET_BIT(DDRC, 6); //OUTPUT
    SET_BIT(PORTC , 6);

    SET_BIT(DDRA, 3); //OUTPUT
    CLR_BIT(PORTA , 3);

    SET_BIT(DDRA, 2); //OUTPUT
    CLR_BIT(PORTA, 2); 

    CLR_BIT(DDRC, 7);   //INPUT
    CLR_BIT(PORTC, 7) ; //pull-up disabled

    CLR_BIT(DDRA, 6); //INPUT
    CLR_BIT(PORTA,6); //pull-up disabled

    CLR_BIT(DDRA, 5);
    CLR_BIT(PORTA,5); 

    ///////////////////
    CLR_BIT(DDRD,  2);   //INPUT
    CLR_BIT(PORTD, 2); //pull-up disabled
}
