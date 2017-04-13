#include "menu.h"
#include "local.h"
#include<avr\io.h>
#include<util\delay.h>

void menu_func_0     (void);
void menu_func_1     (void);
void menu_func_0_0   (void);
void menu_func_0_1   (void);
void menu_func_0_2   (void);
void menu_func_0_3   (void);
void menu_func_1_0   (void);

volatile u8 light_text[20]="LIGHT: TURN  ON   \0";
u8 light_status=0;

Submenus menu0[]={
    {(u8*)"     LED        ",     menu_func_0, 2},
    {(u8*)"    LIGHT       ",     menu_func_1, 2},
};  

Submenus menu0_0[]={
    {(u8*) "LED: LED A   ON ",              menu_func_0_0, 4},
    {(u8*) "LED: LED B  ON " ,              menu_func_0_1, 4},
    {(u8*) "LED: LED AB   ON ",             menu_func_0_2, 4},
    {(u8*) "     <- back    ",        menu_func_0_3, 4}
};  

Submenus menu1_0[]={
    {light_text,                menu_func_1_0, 2},
    {(u8*) "     <- back    ",  menu_func_0_3, 2}
};  

void MENU_init()
{
    MENU_current_menu    = menu0;
    MENU_current_menu_id = 0;
}

void menu_func_0(void)
{
    MENU_current_menu    = menu0_0;
    MENU_current_menu_id = 0;
}

void menu_func_1(void)
{
    MENU_current_menu    = menu1_0;
    MENU_current_menu_id = 0;

    SET_BIT(PORTA, 2);
    _delay_ms(500);
    CLR_BIT(PORTA, 2);
}

void menu_func_0_0(void)
{
    SET_BIT(PORTA, 3);
    _delay_ms(500);
    CLR_BIT(PORTA, 3);
}

void menu_func_0_1(void)
{
    SET_BIT(PORTA, 2);
    _delay_ms(500);
    CLR_BIT(PORTA, 2);
}

void menu_func_0_2(void)
{
     SET_BIT(PORTA, 2);
    _delay_ms(500);
    CLR_BIT(PORTA, 2);

    SET_BIT(PORTA, 3);
    _delay_ms(500);
    CLR_BIT(PORTA, 3);
}

void menu_func_0_3(void)
{
    _delay_ms(500);
    MENU_init();
}

void menu_func_1_0(void)
{
    if (light_status==0) 
    {
        light_status=1;
        CLR_BIT(PORTC, 6);
        //   *light_text = "LIGHT: TURN OFF\0";
        light_text[14]='F';
        light_text[15]='F';
    }
    else
    {
        light_status=0;
        SET_BIT(PORTC, 6);
        //   *light_text= "LIGHT: TURN  ON\0";
        light_text[14]='N';
        light_text[15]=' ';
    }
    _delay_ms(500);
}
