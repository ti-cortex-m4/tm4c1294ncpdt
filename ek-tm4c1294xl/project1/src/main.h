#ifndef __MAIN
#define __MAIN


#include        <stdint.h>
#include        <stdbool.h>
#include        <string.h>
#include        "driverlib/debug.h"
#include        "system.h"
#include        "main_keyboard.h"
#include        "main_serial.h"
#include        "main_tariffs.h"
#include        "main_groups.h"
#include        "main_digitals.h"
#include        "main_energy.h"
#include        "main_events.h"


typedef enum 
{ 
  ANS_BEGIN             =  0,           // начальное состояние
  ANS_TIMEOUT           =  1,           // отработка таймаута
  ANS_ANSWER            =  2            // передача команды
} answer;


// тип 'правило перехода на сезонное время'
typedef enum
{
  DEC_NONE              = 0,
  DEC_AUTO              = 1,
  DEC_CUSTOM            = 2
} decret;


// тип 'режим работы прибора'
typedef enum
{
  GLB_PROGRAM           = 0,
  GLB_WORK              = 1,
  GLB_REPROGRAM         = 2
} global;


#endif






