#include "local.h"
#include "RF.h"
#include "UART.h"

////////////////MODULE 2       - receiver

void RF_port_init()
{
    SET_BIT(RF_PORT, RF_CS);
    SET_BIT(RF_PORT, RF_SDI);
    CLR_BIT(RF_PORT, RF_SCK);
    
    //SDI, CS, SCK outputs
    SET_BIT(RF_DIR, RF_SDI); //OUTPUT
    SET_BIT(RF_DIR, RF_CS);  //OUTPUT
    SET_BIT(RF_DIR, RF_SCK); //OUTPUT

    //NIRQ, SDO inputs, pull-up disable
    CLR_BIT(RF_DIR,  RF_NIRQ);  //INPUT
//    CLR_BIT(M2_PORT, M2_NIRQ) ; //pull-up disabled

    CLR_BIT(RF_DIR,  RF_SDO);  //INPUT
//  CLR_BIT(M2_PORT, M2_SDO) ; //pull-up disabled
}


u16 RF_send_command(u16 cmd)
{
    u8 i;
    u16 recv;
    recv=0;

    RF_LO(RF_SCK);
    RF_LO(RF_CS);

    for (i=0; i<16; i++)
    {
        if (cmd&0x8000) RF_HI(RF_SDI);   //daca bitul curent de transmis e 1 face SDI high
        else RF_LO(RF_SDI);             //daca bitul curent de transmis e 0 face SDI low

        RF_HI(RF_SCK);                //clock-ul HI

        recv<<=1;                    //deplaseaza spre stanga => bitul nou receptionat=0

        if(RF_PIN & (1<<RF_SDO))    //daca SDO e 1
        {
            recv |= 0x0001;         //bitul nou receptionat e facut 1
        }

        RF_LO(RF_SCK);                    //clock-ul LOW
        cmd<<=1;                    //deplaseaza bitii comenzii pt a-l prelua pe urmatorul
    }
    RF_HI(RF_CS);

    return recv;
}



void RF_module_init()
{
    RF_send_command(0x80E7); //EL,EF,868band,12.0pF
    RF_send_command(0x8299); //er,!ebb,ET,ES,EX,!eb,!ew,DC (bug was here)    
    //RF_send_command(0x8239); //!er,!ebb,ET,ES,EX,!eb,!ew,DC      ///////////sender

    RF_send_command(0xA640); //freq select
    //RF_send_command(0xAC80); //frequency select  => 876 MHz
    RF_send_command(0xC647); //4.8kbps
    RF_send_command(0x94A0); //VDI,FAST,134kHz,0dBm,-103dBm
    RF_send_command(0xC2AC); //AL,!ml,DIG,DQD4
    RF_send_command(0xCA81); //FIFO8,SYNC,!ff,DR (FIFO level = 8)
    RF_send_command(0xCED4); //SYNC=2DD4;
    RF_send_command(0xC483); //@PWR,NO RSTRIC,!st,!fi,OE,EN
    RF_send_command(0x9855); //!mp,90kHz,MAX OUT
    RF_send_command(0xCC17); //!OB1,!OB0, LPX,!ddy,DDIT,BW0
    RF_send_command(0xE000); //NOT USE
    RF_send_command(0xC800); //NOT USE
    RF_send_command(0xC040); //1.66MHz,2.2V
}

int RF_receive()
{
    u16 data;
    u16 Timeout_loop = 64500;

    while(1 & (++Timeout_loop != 0))
    {
        data = RF_send_command(0x0000);

        if (data & 0x8000)
        {
            data=RF_send_command(0xB000);
            return (data & 0x00FF);
        }
    }
    return TIMEOUTLOOP_EXPIRAT; //a expirat timeoutloop
}

void RF_send_data(u8 data)
{
    //when the module is configured in transmitter mode
    //NIRQ goes low when previous data has been sent

    while(RF_PIN & (1<<RF_NIRQ)) {} ;
    RF_send_command(0xB800 | data); 
}

void RF_fifo_reset()
{
    RF_send_command(0xCA81);
    RF_send_command(0xCA83);
}

void RF_send_headder(char system_addr, char dest_addr)
{
    u8 data=0;
    data=system_addr<<5;          //primii 3 biti reprezinta nr sistemului
    data |= (dest_addr & 0x1F);   //ultimii 5 biti reprezinta nr modulului destinatie

    RF_send_data(data);
}

void RF_get_headder(char *system_addr, char *dest_addr)
{
    u8 dat = RF_receive();

    *system_addr = dat >> 5;        //extrage primii 3 biti
    *dest_addr   = (dat & 0x1F);    //extrage ultimii 5 biti
}




