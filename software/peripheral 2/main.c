////////////////////////////////PERIFERIC/////////////////////////
#include "OS.h"
#include "data.h"


#include <avr\interrupt.h>



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

	////////////ADC initializare//////////////
	ADMUX  = 0x47;  //0100 0111  - external reference, allign result right, ADC7 single input
	ADCSRA = 0x86;  //1000 0110  - enable ADC, interrupt disable, clock prescaler = 64
//u8 intrare=0x00, iesire=0x00;

while(1)
{
//DATA_code(0x0A, &iesire);

//DATA_decode(iesire^0x03, &intrare);

	OS_run();
}

   


return(0);
   
}


/*
ISR(INT0_vect) 
{

	RF_M2_send_command(0xCA83);

	//RECEIVE 
	//wait for data

	dat=RF_M2_receive();

	UART_Send('\n');
	UART_Send('D');
	UART_Send(dat);
	UART_Send('\n');

//	dat=RF_M2_receive();
//	UART_Send(dat);

	for (i=0; i<65000; i++) for (j=0; j<65003; j++);
	for (i=0; i<65000; i++) for (j=0; j<65003; j++);
	for (i=0; i<65000; i++) for (j=0; j<65003; j++);
	for (i=0; i<65000; i++) for (j=0; j<65003; j++);
	for (i=0; i<65000; i++) for (j=0; j<65003; j++);

//	RF_M2_fifo_reset();

//	RF_M2_send_command(0xCA81);

	LED1_ON();
	LED2_ON();

	
}
*/

/*

//interrupt <-> match between OCR2 and TCNT2 - timer counter 2 registers
//aprox. 10kHz IR reading
ISR(TIMER0_COMP_vect) 
{
u8 current= (u8) GET_BIT(PINC, 7);

if ((current==0) && (start==0)) start=1;


if (start)
{
 k++;
 matrice[k]=current;
}


}
*/









