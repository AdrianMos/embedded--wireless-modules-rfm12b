////////////////////////////////PERIFERIC/////////////////////////
#include "OS_conf.h"
#include "local.h"
#include "pin.h"
#include "UART.h"
#include "RF.h"
#include "data.h"

u8 system_addr, dest_addr;
u8 ADC_data = 0;

void OS_run()
{
    u8 j;
    //daca a mai trecut un interval de timp decrementeaza timpul ramas 
    //pana la executie pentru fiecare task
    if(GET_BIT(TIFR, OCF0))
    {
        for(j=0; j<os_config.tasks_nr; j++)
        {
            if(os_config.tasks[j].remaining_time>0)
               os_config.tasks[j].remaining_time--;
        }
        SET_BIT(TIFR, OCF0); //reseteaza flagul
    }

    //executa task-ul daca timpul ramas pana la executie==0
    //si reinitializeaza timpul ramas
    for(j=0; j<os_config.tasks_nr; j++)
    {
        if(os_config.tasks[j].remaining_time==0)
        {
           os_config.tasks[j].task_handler();
           os_config.tasks[j].remaining_time=os_config.tasks[j].period;
        }
    }
}

//initializare clock pentru OS
void OS_tasks_clock_init(void)
{
    //enable interrupt on match      --   Timer/Counter Interrupt Mask
    //SET_BIT(TIMSK, 1);       
    //00001011
    TCCR0=0x0B;
    OCR0 = 15; //->128us   
}

void OS_init(void)
{
    u8 i,j;

    PIN_init();
    //UART_init();
    OS_tasks_clock_init();

    RF_port_init();
    for (i=0; i<100; i++) for (j=0; j<100; j++); //delay
    RF_module_init();

    LED1_OFF();
    LED2_OFF();
}

void task2_receptie_comanda_si_transmisie_stare(void)
{
    if ((GET_BIT(PINC, 5)==0))  
        LED2_ON();

    RF_send_command(0x0000);
    RF_send_command(0x8299); // intra in mod receptie 
    RF_send_command(0xCA83);


    //RECEIVE 
    //wait for data
    u8 header, dat;
    
    ///////trebuie tratata si eroarea ce poate aparea la datele de receptie
    ///////n-a fost tratata pt ca modulul central sa nu ramana in bucla
    //infinita asteptand datele de la periferic
    //if(                                      ////////////////////de tratat erorile
    DATA_receive_and_decode(&header);
    // != DATA_EROARE_DUBLA)
    {
            DATA_receive_and_decode(&dat);

            RF_fifo_reset();

        //daca headerul receptionat coincide cu headerul modulului curent
        if (header == GLOBAL_DEST_ADDR(SYSTEM_ADDR, CURRENT_ADDR))
        {
            if (dat=='X')      //daca a receptionat cerere transmite informatia de raspuns
            {
                //SEND
                RF_send_command(0x0000);
                RF_send_command(0x8239);    // intra in mod emisie

                RF_send_data(0xAA);   //preambul
                RF_send_data(0xAA);
                RF_send_data(0xAA);
                RF_send_data(0x2D);   //sincronizare
                RF_send_data(0xD4); 

                ////////////////////DATE UTILE///////////
                //transmite headerul (8 biti)
                DATA_code_and_send(GLOBAL_DEST_ADDR(SYSTEM_ADDR, MASTER_ADDR));

                if ((GET_BIT(PINC, 5)==0))
                {
                    DATA_code_and_send(99);
                    LED1_ON();
                }
                else 
                {
                    DATA_code_and_send(ADC_data);    
                }                                    
                //////////////////////////////////////////

                RF_send_data(0xAA);   //dummy bytes
                RF_send_data(0xAA);
                RF_send_data(0xAA);
            }
        }
    }             
}

void task_ADC(void)
{
    SET_BIT(ADCSRA, 6); //START CONVERSION

    while (!GET_BIT(ADCSRA, 4)) {};
    
    u16 aux=ADCL | (ADCH<<8);
    ADC_data = (u8 ) (aux * 500 / 1024);
}
    

