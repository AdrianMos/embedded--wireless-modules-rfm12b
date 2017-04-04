
#include<avr\io.h>

#include "local.h"
#include "UART_conf.h"

void UART_init()
{
u16 ubrr=UART_CALCULATED_UBRR;

/* Set baud rate */
UBRRH = (u8) (ubrr>>8);

UBRRL = (u8 )ubrr;


/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN);

/* Set frame format: 8data, 2stop bit */
UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void UART_Send( u8 data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) );

/* Put data into buffer, sends the data */
UDR = data;
}

u8 UART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSRA & (1<<RXC)) )
;
/* Get and return received data from buffer */
return UDR;
}

