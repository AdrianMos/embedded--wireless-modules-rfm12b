#ifndef LOCAL_H
#define LOCAL_H

#include<avr/io.h>

#define SET_BIT(REG, BIT) (  (REG)=( (REG)| (1<<(BIT)) )  )
#define CLR_BIT(REG, BIT) (  (REG)=( (REG) & ~(1<<(BIT))))
#define GET_BIT(REG, BIT) ( ((REG) & (1<<(BIT)))>0 ? 1 : 0) 

#define LED1_OFF() PORTD &=~(1<<4)
#define LED1_ON()  PORTD |= (1<<4)

#define LED2_OFF() PORTD &=~(1<<5)
#define LED2_ON()  PORTD |= (1<<5)

typedef unsigned char u8;
typedef unsigned int u16;

#endif
