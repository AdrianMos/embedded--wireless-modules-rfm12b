#ifndef MENU_H
#define MENU_H

#include "local.h"

typedef   void (*ptr_func)(void);

typedef struct {
	u8 *text;
	ptr_func menu_function;
	u8 max_id;
	} Submenus;


extern void MENU_init();
extern void MENU_enter();
extern void MENU_next_option();
extern void MENU_previous_option();
extern void MENU_display_option();

extern Submenus * MENU_current_menu;
extern u8         MENU_current_menu_id;

#endif
