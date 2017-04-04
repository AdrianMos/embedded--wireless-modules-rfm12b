#ifndef OS_CONF_H
#define OS_CONF_H

#include "os.h"

#define SYSTEM_ADDR  1  //adresa sistemului
#define CURRENT_ADDR 0  //adresa modulului curent

#define MODULE1_ADDR 0x01  //adresa  modul1
#define MODULE2_ADDR 0x02  //adresa  modul1

//extern Task os_tasks[];
extern OS_Config_struct os_config;  //declara o structura de tip OS_Config_struct


#endif
