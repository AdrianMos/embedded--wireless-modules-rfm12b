#include "local.h"
#include "menu.h"
#include "lcd.h"
#include "menu_cnf.h"

Submenus * MENU_current_menu;
u8 MENU_current_menu_id=0;

void MENU_display_option()
{
    LCD_clear();
    LCD_write_text(MENU_current_menu[MENU_current_menu_id].text);
}

void MENU_next_option()
{
    if (MENU_current_menu_id <MENU_current_menu[0].max_id-1) 
        MENU_current_menu_id++;
    else if (MENU_current_menu_id == MENU_current_menu[0].max_id-1)
        MENU_current_menu_id=0;
}

void MENU_previous_option()
{
    if (MENU_current_menu_id > 0)       
        MENU_current_menu_id--;
    else if (MENU_current_menu_id == 0)  
        MENU_current_menu_id= MENU_current_menu[0].max_id-1;
}

void MENU_enter()
{
    MENU_current_menu[MENU_current_menu_id].menu_function();
}
