#ifndef UART_H
#define UART_H

#include "local.h"

extern void UART_init();
extern void UART_Send( u8 data );
extern u8   UART_Receive( void );

#endif
