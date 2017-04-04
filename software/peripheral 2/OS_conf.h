#ifndef OS_CONF_H
#define OS_CONF_H

#include "os.h"

#define SYSTEM_ADDR     0x01        //adresa sistemului

#define CURRENT_ADDR    0x02        //adresa modulului curent
#define MASTER_ADDR     0x00        //adresa modulului master




//extern Task os_tasks[];
extern OS_Config_struct os_config;  //declara o structura de tip OS_Config_struct
extern void task_ADC(void);

#endif
