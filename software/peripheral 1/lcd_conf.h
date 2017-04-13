#ifndef LCD_CONF_H
#define LCD_CONF_H


/*current config
RS					-> PORTD pin 2
RW					-> PORTD pin 5
EN                  -> PORTD pin 7
DB4, DB5, DB6, DB7  -> PORTC pins 0,1,2,3

!!ALL DATA PINS MUST BE ON THE SAME PORT
*/

//dirrection registers for control lines
#define RS_PORT_DIR DDRD
#define RW_PORT_DIR DDRD
#define EN_PORT_DIR DDRD

//data registers for control lines
#define RS_PORT PORTD
#define RW_PORT PORTD
#define EN_PORT PORTD

//pin number for control lines
#define RS 2 //pin 2 
#define RW 5 //pin 5
#define EN 7 //pin 7

//dirrection registers for data lines
#define DB_PORT_DIR   DDRC


#define DB_PORT      PORTC    //data register for data lines
#define DB_PORT_READ PINC     //input data register for data lines  

//pin number for data lines
#define DB4 0 //pin 0
#define DB5 1 //pin 1
#define DB6 2 //pin 2
#define DB7 3 //pin 3

#endif
