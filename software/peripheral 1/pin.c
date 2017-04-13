#include "local.h"

void PIN_init()
{
    ////BUTOANE

    CLR_BIT(DDRC, 2);   //INPUT
    SET_BIT(PORTC, 2) ; //pull-up ENABLED

    CLR_BIT(DDRC,1);   //INPUT
    SET_BIT(PORTC, 1) ; //pull-up ENABLED

    CLR_BIT(DDRC, 0);   //INPUT
    SET_BIT(PORTC, 0) ; //pull-up ENABLED


    ////////LEDURI
    SET_BIT(DDRD, 4); //OUTPUT
    CLR_BIT(PORTD , 4);

    SET_BIT(DDRD, 5); //OUTPUT
    CLR_BIT(PORTD , 5);

    SET_BIT(DDRD, 6); //OUTPUT
    CLR_BIT(PORTD, 6); 

    SET_BIT(DDRD, 7); //OUTPUT
    CLR_BIT(PORTD, 7); 
}
