#include "local.h"


void PIN_init()
{
////////////////////////RFM12B/////////////////////

SET_BIT(DDRC, 7); //SDI - OUTPUT
CLR_BIT(PORTC,7);

SET_BIT(DDRC, 6); //SCK - OUTPUT
CLR_BIT(PORTC,6);

CLR_BIT(DDRC, 5); //SDO - INPUT
CLR_BIT(PORTC,5); //      pull-up disable


SET_BIT(DDRC, 4); //SEL - OUTPUT
CLR_BIT(PORTC,4);

CLR_BIT(DDRC, 3); //IRQ - INPUT
CLR_BIT(PORTC,3); //      pull-up disabled



//////////////////BUTOANE//////////////////////////
CLR_BIT(DDRD,  4);   //INPUT
SET_BIT(PORTD, 4) ; //pull-up enable

CLR_BIT(DDRD,  5);   //INPUT
SET_BIT(PORTD, 5) ; //pull-up enable

CLR_BIT(DDRD,  6);   //INPUT
SET_BIT(PORTD, 6) ; //pull-up enable

CLR_BIT(DDRD,  7);   //INPUT
SET_BIT(PORTD, 7) ; //pull-up enable


//////////////////BUZZER///////////////////////////
SET_BIT(DDRD,  2); 
CLR_BIT(PORTD, 2);


//////////////////SEGMENT DISPLAY /////////////////
//////////////////PORT A CA IESIRI ////////////////
DDRA=0XFF;
PORTA=0X00;

//pinii de selectie display
SET_BIT(DDRB,  0); 
CLR_BIT(PORTB, 0);

SET_BIT(DDRB,  1);
CLR_BIT(PORTB, 1);

SET_BIT(DDRB,  2);
CLR_BIT(PORTB, 2);

SET_BIT(DDRB,  3);
CLR_BIT(PORTB, 3);


}
