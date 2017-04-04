//////////////////////////////CENTRAL////////////////////////
#include "OS_conf.h"
#include "local.h"
#include "pin.h"
#include "UART.h"
#include "RF.h"
#include "data.h"

#include "display.h"

#include <avr\interrupt.h>


u8 system_addr, dest_addr;

u8 DISP_segment_nr=0;        
u8 DISP_perif_nr = 0;              //retine numarul perifericului ce se afiseaza momentan
u8 DISP_perif_alias =  DISP_ZERO;  //retine caracterul ce trebuie afisat pe display pentru perifericul curent
u8 DISP_data[3][2]={{DISP_MINUS,DISP_MINUS}, {DISP_MINUS,DISP_MINUS}}; //retine caracterul 3 si 4 de afisat pentru fiecare periferic. DISP_data[nr_modul][nr_caracter]



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

  PORTA=0XFF;

  PIN_init();
//  UART_init();
  OS_tasks_clock_init();

 RF_port_init();
 for (i=0; i<100; i++) for (j=0; j<100; j++); //delay ????????
 RF_module_init();

}



///////////////////////////////////////////TASK-URI////////////////////////////////////////



void task1_interogheaza_perif1(void)
{


 
// if(GET_BIT(PIND, 4)==0)
 {
  	////////////////////////TRANSMITE CERERE
	RF_send_command(0x0000);



	RF_send_command(0x8239);         //mod emisie

	RF_send_data(0xAA);  //preabul
	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0x2D);  //sincronizare
	RF_send_data(0xD4);



	/////////////////////////////DATE UTILE////////////////////
	
	DATA_code_and_send(GLOBAL_DEST_ADDR(SYSTEM_ADDR, MODULE1_ADDR));
	DATA_code_and_send('X');

	///////////////////////////////////////////////////////////

	RF_send_data(0xAA);   //dummy bytes
	RF_send_data(0xAA);
	RF_send_data(0xAA);

///////////////////////////// RECEPTIE RASPUNS ///////////////////////////
	RF_send_command(0x0000);
	RF_send_command(0x8299); // intra in mod receptie 

	RF_send_command(0xCA83);

	///////////////////// RECEIVE //////////////////////////// 

	u8 header, dat;
	int err0, err1;
 	err0= DATA_receive_and_decode(&header);
	err1= DATA_receive_and_decode(&dat);

	if ((err0==TIMEOUTLOOP_EXPIRAT) || (err1==TIMEOUTLOOP_EXPIRAT))
   	{
	 	DISP_data[1][0]=DISP_E;
		DISP_data[1][1]=DISP_ZERO;
   	}	
	else
	if (header == GLOBAL_DEST_ADDR(SYSTEM_ADDR,CURRENT_ADDR))
	{

		DISP_genereaza_caracterele(dat, &DISP_data[1][0], &DISP_data[1][1]);
	

		if (dat=='A')
		{
			BUZZER_ON();
		}
		else if (dat=='B')
		{
	
		}
		else if (dat=='C')
		{
		
			DISP_perif_nr++;
			DISP_perif_nr %= 2;

			if      (DISP_perif_nr == 0 ) DISP_perif_alias = DISP_ZERO;
			else if (DISP_perif_nr == 1 ) DISP_perif_alias = DISP_UNU;
	

		}
		else if (dat=='D')
		{

		}
		else 
		{
		  BUZZER_OFF();

		  DISP_data[1][0]=DISP_ZERO;
		  DISP_data[1][1]=DISP_ZERO;
		  
		}
 	}
 }
 
}

void task2_interogheaza_perif2(void)
{
	////////////////////////TRANSMITE CERERE
	RF_send_command(0x0000);



	RF_send_command(0x8239);         //mod emisie

	RF_send_data(0xAA);  //preabul
	RF_send_data(0xAA);
	RF_send_data(0xAA);
	RF_send_data(0x2D);  //sincronizare
	RF_send_data(0xD4);



	/////////////////////////////DATE UTILE////////////////////
	
 	DATA_code_and_send(GLOBAL_DEST_ADDR(SYSTEM_ADDR, MODULE2_ADDR));
	DATA_code_and_send('X');

	///////////////////////////////////////////////////////////

	RF_send_data(0xAA);   //dummy bytes
	RF_send_data(0xAA);
	RF_send_data(0xAA);

///////////////////////////// RECEPTIE RASPUNS ///////////////////////////
	RF_send_command(0x0000);
	RF_send_command(0x8299); // intra in mod receptie 

	RF_send_command(0xCA83);

	///////////////////// RECEIVE //////////////////////////// 

	u8 header, dat;
	int err0, err1;
    err0=DATA_receive_and_decode(&header);
	err1=DATA_receive_and_decode(&dat);


   if ((err0==TIMEOUTLOOP_EXPIRAT) || (err1==TIMEOUTLOOP_EXPIRAT))
   {
	 	DISP_data[0][0]=DISP_E;
		DISP_data[0][1]=DISP_ZERO;
   }
   else


	if (header == GLOBAL_DEST_ADDR(SYSTEM_ADDR,CURRENT_ADDR))
	{
	
	    DISP_genereaza_caracterele(dat, &DISP_data[0][0], &DISP_data[0][1]);

 	}
 



}


void task3_citeste_butoanele(void)
{

if (GET_BIT(PIND, 4)==0) //buton dreapta sus
{
	DISP_perif_nr++;
	DISP_perif_nr %= 2;

	if      (DISP_perif_nr == 0 ) DISP_perif_alias = DISP_ZERO;
	else if (DISP_perif_nr == 1 ) DISP_perif_alias = DISP_UNU;
}

/*
CLR_BIT(DDRD,  4);   //INPUT
SET_BIT(PORTD, 4) ; //pull-up enable

CLR_BIT(DDRD,  5);   //INPUT
SET_BIT(PORTD, 5) ; //pull-up enable

CLR_BIT(DDRD,  6);   //INPUT
SET_BIT(PORTD, 6) ; //pull-up enable

CLR_BIT(DDRD,  7);   //INPUT
SET_BIT(PORTD, 7) ; //pull-up enable
*/

}

//interrupt <-> match between OCR2 and TCNT2 - timer counter 2 registers
//AFISEAZA DATELE
ISR(TIMER2_COMP_vect) 
{


/*

	switch (DISP_segment_data)
	{

		case '0': 	PORTA=DISP_ZERO;
					break;

		case '1': 	PORTA=DISP_UNU;
					break;

		case '2': 	PORTA=DISP_DOI;
					break;

		case '3': 	PORTA=DISP_TREI;
					break;

		case '4': 	PORTA=DISP_PATRU;
					break;

		case '5': 	PORTA=DISP_CINCI;
					break;

		case '6': 	PORTA=DISP_SASE;
					break;

		case '7': 	PORTA=DISP_SAPTE;
					break;

		case '8': 	PORTA=DISP_OPT;
					break;

		case '9': 	PORTA=DISP_NOUA;
					break;


		case '-': 	PORTA=DISP_MINUS;
					break;

		case 'P': 	PORTA=DISP_P;
					break;

		case 'E': 	PORTA=DISP_E;
					break;


		default:    PORTA=0XFF;	//nu afiseaza nimic
					break;
	}
*/

	DISP_segment_nr=(DISP_segment_nr+1) % 5;

	switch (DISP_segment_nr)
	{
		case 1:	//afiseaza caracterul corespunzator perifericului curent
				
				PORTA=DISP_perif_alias;		
				PORTB=0X01;	
				break;

		case 2:	
			                     	
				PORTA=DISP_MINUS;				
				PORTB=0X02;

			//	SET_DOT_POINT(PORTA);
				break;

		case 3:	                    //afiseaza datele perifericului curent [caracterul 3]
				PORTA=DISP_data[DISP_perif_nr][0];				
				PORTB=0X04;

				break;
		case 4:						//afiseaza datele perifericului curent [caracterul 4]
				PORTA=DISP_data[DISP_perif_nr][1];
				PORTB=0X08;
				break;
	}
 

}
