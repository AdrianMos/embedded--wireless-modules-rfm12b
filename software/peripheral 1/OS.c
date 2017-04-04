////////////////////////////////PERIFERIC/////////////////////////
#include "OS_conf.h"
#include "local.h"
#include "pin.h"
#include "UART.h"
#include "RF.h"
#include "data.h"



u8 system_addr, dest_addr;

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
     if(os_config.tasks[j].remaining_time==0)
     {
           os_config.tasks[j].task_handler();
           os_config.tasks[j].remaining_time=os_config.tasks[j].period;
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



//initializare OS
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



///////////////////////////////////////////TASK-URI////////////////////////////////////////
/*
void task0(void)
{
u16 a, b;

  if(GET_BIT(PINC, 2)==0)      
  {

	LED1_OFF();
 	LED2_ON();


	//SEND
	RF_send_command(0x0000);
	RF_send_command(0x8239);

	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0x2D);
	RF_send_data(0xD4);

//	for (i=0; i<32; i++)
//	{
	RF_send_data('A');
//}


	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0xAA);


	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);

  }
}
*/
/*
void task1(void)
{
u16 a, b;

  if(GET_BIT(PINC, 1)==0)    
  {
    RF_send_command(0xA640); 


 	LED1_ON();
	LED2_OFF();


	//SEND
	RF_send_command(0x0000);
	RF_send_command(0x8239);

	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0x2D);
	RF_send_data(0xD4);

//	for (i=0; i<32; i++)
//	{
	RF_send_data('B');

//	}

	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0xAA);


	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);
	for (a=0; a<60000; a++) for (b=0; b<60003; b++);

  }

}
*/

void task2_receptie_comanda_si_transmisie_stare(void)
{
	RF_send_command(0x0000);
	RF_send_command(0x8299); // intra in mod receptie 


	RF_send_command(0xCA83);


	//RECEIVE 
	//wait for data
	u8 header, dat;
	
	///////trebuie tratata si eroarea ce poate aparea la datele de receptie
	///////n-a fost tratata pt ca modulul central sa nu ramana in bucla
	//infinita asteptand datele de la periferic
//if(
 DATA_receive_and_decode(&header); //de tratat eroarea
 //!= DATA_EROARE_DUBLA)
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
		RF_send_command(0x8239);	// intra in mod emisie

		RF_send_data(0xAA);   //preambul
		RF_send_data(0xAA);
		RF_send_data(0xAA);
		RF_send_data(0x2D);   //sincronizare
		RF_send_data(0xD4); 


		////////////////////DATE UTILE///////////

		//transmite headerul (8 biti)
		DATA_code_and_send(GLOBAL_DEST_ADDR(SYSTEM_ADDR, MASTER_ADDR));

		if ((GET_BIT(PINC, 1)==0) && (GET_BIT(PINC, 1)==0))   DATA_code_and_send('D');
		else if(GET_BIT(PINC,  2)==0)                         DATA_code_and_send('A');
		else if (GET_BIT(PINC, 1)==0)                         DATA_code_and_send('B');
		else if (GET_BIT(PINC, 0)==0)                         DATA_code_and_send('C');
		else 												  DATA_code_and_send(0);

	
		//////////////////////////////////////////

		RF_send_data(0xAA);   //dummy bytes
		RF_send_data(0xAA);
		RF_send_data(0xAA);
  	}
}
}
				 
}
	

