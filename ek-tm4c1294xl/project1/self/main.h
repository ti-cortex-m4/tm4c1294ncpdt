/*------------------------------------------------------------------------------
MAIN,H


------------------------------------------------------------------------------*/

#ifndef __MAIN
#define __MAIN


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "driverlib/debug.h"
#include "system.h"
#include "main_keyboard.h"
#include "main_serial.h"
#include "main_tariffs.h"
#include "main_groups.h"
#include "main_digitals.h"
#include "main_energy.h"
#include "main_events.h"
#include "main_storage.h"
#include "main_defines.h"
#include "main_params.h"
#include "main_extended.h"
#include "main_correct.h"
#include "kernel/bool.h"
#include "kernel/number.h"
#include "kernel/float.h"
#include "kernel/tuples.h"
#include "kernel/wrappers.h"



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
