#include<avr/io.h>
#include<util/delay.h>

#include "lcd.h"
#include "local.h"
#include "lcd_conf.h"

void LCD_init  ( void );
void LCD_write ( u8 value );
void LCD_clear ( void );
void LCD_delay ( void );
void LCD_send_command ( u8 com );
void LCD_write_text(u8 *str);
void LCD_scroll_text(u8 *str);
void LCD_set_cursor(u8 position);


void DB_AS_OUTPUTS()
{
    SET_BIT(DB_PORT_DIR, DB7); //set db5-db7 as outputs
    SET_BIT(DB_PORT_DIR, DB6);
    SET_BIT(DB_PORT_DIR, DB5);
    SET_BIT(DB_PORT_DIR, DB4);
}

void CTRL_AS_OUTPUTS()
{
    SET_BIT(RS_PORT_DIR, RS); //set control bits as outputs
    SET_BIT(RW_PORT_DIR, RW);
    SET_BIT(EN_PORT_DIR, EN);
}

void LCD_init( void ) //LCD FUNCTIONING MODE
{
    //set pins as outputs
    DB_AS_OUTPUTS();
    CTRL_AS_OUTPUTS();

    ///////////////////////////////////////
    CLR_BIT(RW_PORT, RW); //RW = 0
    CLR_BIT(EN_PORT, EN); //EN = 0
    CLR_BIT(RS_PORT, RS); //RS = 0


    //The first instruction we send must tell the LCD we'll be communicating 
    //with it with a 4-bit data bus. We also select a 5x8 dot character font.
    //These two options are selected by sending the command 28h to the LCD as
    //a command. After powering up the LCD, it is in 8-bit mode. Because only
    // four bits are connected, the first command has to be send twice; 
    //the first time to switch to 4-bits mode, (the lower 4 bits of the 
    //command are not seen), the second time to send it as two nibbles 
    //so the lower part is received, too.

    SET_BIT(EN_PORT, EN); //EN = 1

    CLR_BIT(DB_PORT, DB7);     //0x28 -> just 2 is sent first time
    CLR_BIT(DB_PORT, DB6);
    SET_BIT(DB_PORT, DB5);
    CLR_BIT(DB_PORT, DB4);

    CLR_BIT(EN_PORT, EN); //EN = 0

    LCD_delay();
    _delay_ms(12);

    //4 bit mode, double line and 5x7 dot character format 
    LCD_write(0X28); LCD_delay();
    LCD_write(0X28); LCD_delay();
    LCD_write(0X28); LCD_delay();

    LCD_write(0X0C); //Display "ON", cursor line "ON"
    LCD_delay();

    _delay_ms(12);

    LCD_write(0X06); //Cursor travel upon data entry to the right 
    LCD_delay();

    _delay_ms(12);
     
    LCD_clear();
}

void LCD_write(u8 value)
{
    DB_AS_OUTPUTS();

    SET_BIT(EN_PORT, EN);
    
    //higher nibble
    if(value & 0x10) SET_BIT(DB_PORT, DB4); else CLR_BIT(DB_PORT, DB4);
    if(value & 0x20) SET_BIT(DB_PORT, DB5); else CLR_BIT(DB_PORT, DB5);
    if(value & 0x40) SET_BIT(DB_PORT, DB6); else CLR_BIT(DB_PORT, DB6);
    if(value & 0x80) SET_BIT(DB_PORT, DB7); else CLR_BIT(DB_PORT, DB7);

    CLR_BIT(EN_PORT, EN); //toggle enable line=>LCD reads input pins
    SET_BIT(EN_PORT, EN);

    //lower nibble
    if(value & 0x01) SET_BIT(DB_PORT, DB4); else CLR_BIT(DB_PORT, DB4);
    if(value & 0x02) SET_BIT(DB_PORT, DB5); else CLR_BIT(DB_PORT, DB5);
    if(value & 0x04) SET_BIT(DB_PORT, DB6); else CLR_BIT(DB_PORT, DB6);
    if(value & 0x08) SET_BIT(DB_PORT, DB7); else CLR_BIT(DB_PORT, DB7);

    CLR_BIT(EN_PORT, EN); //toggle enable line=>LCD reads input pins
}

void LCD_clear()
{
    LCD_send_command(LCD_CLEAR);

    //clearing the LCD takes longer than usual waiting time
    //to be removed when implementing LCD check busy status algorithm
    _delay_ms(3);           

}

void LCD_send_command(u8 com)
{    
    CLR_BIT(RS_PORT, RS); //set command mode
    LCD_write(com);
    LCD_delay();
    SET_BIT(RS_PORT, RS); //restore data mode
}

void LCD_delay()
{
    //when reading LCD busy status <-> LCD_wait function is implemented
    //just replace this with LCD_wait();
    _delay_us(100);
}

void LCD_write_text(u8 *str)
{
    u8 *i=str;
    
    SET_BIT(RS_PORT, RS);
    while (*i)
    {
        LCD_write(*i);
        i++;
        LCD_delay();
    }
}

void LCD_scroll_text(u8 *str)
{
    u8 *start        = str;
    u8 *current_char = str;

    while (*start)
    {
        LCD_clear();
        
        for(int i = 0; i<18; i++)
        {
            LCD_write(*current_char);
            LCD_delay();
            current_char++;

            if(*current_char=='\0') 
                break;
        }
        _delay_ms(250);
        start++;
        current_char=start;
    }    
}

void LCD_set_position(u8 position)
{
    // position 0-15  <-> first line
    // position 16-32 <-> second line

    if(position<=16)   //move cursor on the first line at specified position
      LCD_send_command (position+0x80 ); 
    else 
      //move cursor on the second line at specified position
      LCD_send_command (LCD_NEXT_LINE + position - 16 -1); 
}
