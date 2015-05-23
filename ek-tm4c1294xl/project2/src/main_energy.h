/*------------------------------------------------------------------------------
MAIN_ENERGY.H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// тип 'время/дата + значение'
typedef struct
{
  time          tiSelf;                 // время/дата
  real          reSelf;                 // значение
} value;


// тип 'максимум мощности по тарифам'
typedef struct
{
  value         mpmaMax[bTARIFFS];
} power;


// тип 'количество импульсов по тарифам'
typedef struct
{
  ulong         mpdwImp[bTARIFFS];
} impulse;
