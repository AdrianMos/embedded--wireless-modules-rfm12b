#ifndef OS_H
#define OS_H

#include "local.h"

//defineste ptr_functie ca tip de data  pointer la functie
typedef   void (*ptr_func)(void);


//defineste o structura ce descrie un task
typedef struct {
  u16 remaining_time;		//timpul ramas pana la executarea task-ului
  u16 period;				//perioada task-ului
  ptr_func task_handler;	//pointer la functia ce o executa task-ul
} Task_struct;


//defineste o structura ce descrie toate task-urile
typedef struct {
  u8 tasks_nr;                //nr total de taskuri
  Task_struct *tasks;		  //pointer la o structura ce descrie task-ul
} OS_Config_struct;


extern void OS_init(void);
extern void OS_run();



extern void task1_interogheaza_perif1(void);
extern void task2_interogheaza_perif2(void);
extern void task3_citeste_butoanele(void);

#endif
