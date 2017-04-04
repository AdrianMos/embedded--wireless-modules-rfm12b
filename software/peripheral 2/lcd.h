#ifndef LCD_lib_H
#define LCD_lib_H

#include "local.h"

#define LCD_NEXT_LINE 0xC0 //move cursor to next line
#define LCD_CLEAR     0x01 //clear screen



extern void LCD_set_position (u8 pos  );
extern void LCD_send_command (u8 com  );
extern void LCD_init         (void    );
extern void LCD_write_text   (u8 * mes);
extern void LCD_clear        (void    );
extern void LCD_scroll_text  (u8 *str );




#endif
