#ifndef LOCAL_H
#define LOCAL_H

#include<avr/io.h>


#define SET_BIT(REG, BIT) (  (REG)=( (REG)| (1<<(BIT)) )  )
#define CLR_BIT(REG, BIT) (  (REG)=( (REG) & ~(1<<(BIT))))

#define GET_BIT(REG, BIT) ( ((REG) & (1<<(BIT)))>0 ? 1 : 0) 



#define LED1_OFF() PORTA &=~(1<<2)
#define LED1_ON()  PORTA |= (1<<2)

#define LED2_OFF() PORTA &=~(1<<3)
#define LED2_ON()  PORTA |= (1<<3)

#define BUZZER_ON()  (PORTD |= (1<<2))
#define BUZZER_OFF() (PORTD &= ~(1<<2))
		

#define TIMEOUTLOOP_EXPIRAT 0x04000


typedef unsigned char u8;
typedef unsigned int u16;

#endif
