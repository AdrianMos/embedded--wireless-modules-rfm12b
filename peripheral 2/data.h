#ifndef DATA_H
#define DATA_H

#define DATA_EROARE_DUBLA 0xF0
#define GLOBAL_DEST_ADDR(x,y) ((x<<5) | (y & 0x1F))

extern void DATA_code_and_send(u8 in);
extern u8   DATA_receive_and_decode(u8 *out);

#endif
