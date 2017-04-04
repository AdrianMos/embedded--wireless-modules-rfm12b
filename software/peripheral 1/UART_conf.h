#ifndef UART_CONF_H
#define UART_CONF_H

#define FOSC 8000000
#define BAUD 9600
#define UART_CALCULATED_UBRR (FOSC/16/BAUD-1)

#endif
