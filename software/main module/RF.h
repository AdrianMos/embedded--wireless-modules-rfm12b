#ifndef RF_H
#define RF_H

//modul 1 - portC   --- MODUL CENTRAL
#define RF_SDI  7
#define RF_CS   4
#define RF_SCK  6
#define RF_NIRQ 3
#define RF_SDO  5
#define RF_PORT PORTC
#define RF_PIN  PINC
#define RF_DIR  DDRC

#define RF_HI(x)  RF_PORT |=  (1<<(x))
#define RF_LO(x)  RF_PORT &= ~(1<<(x))

extern void RF_port_init();
extern u16  RF_send_command(u16 cmd);
extern void RF_module_init();
extern void RF_send_data(u8 data);
extern int  RF_receive();
extern void RF_fifo_reset();

extern void RF_get_headder();
extern void RF_send_headder(char system_nr, char dest_module_nr);

#endif
