////////////////////////////////PERIFERIC/////////////////////////
#include "OS_conf.h"
#include "local.h"
#include "OS.h"


//declara un tablou de structuri (de tip  Task_struct) 
//in acest tablou se declara task-urile ce se doresc a fi executate

Task_struct os_tasks[]={
  // {2 ,  2, task0}, 
  // {2,   2, task1}
   {3,   3, task2_receptie_comanda_si_transmisie_stare}
};


//  Task
//  {
//     u16 remaining_time;  
//     u16 period;
//     ptr_func task_handler;
//  }


//declara o structura ce include numarul total de task-uri si un pointer catre tabloul de task-uri
OS_Config_struct os_config = { 
							sizeof(os_tasks)/sizeof(os_tasks[0]),  //numarul de task-uri
							os_tasks							   //pointer catre tabloul de task-uri
					  };

//	OS_Config 
// {
//      u8 tasks_nr;
//     Task *tasks;
// }
