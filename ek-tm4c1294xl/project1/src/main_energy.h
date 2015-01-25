#include        "main_basic.h"



// тип 'максимум мощности'
typedef struct
{
  time          tiNow;                  // время/дата
  real          rePow;                  // значение максимума мощности
} maximum;


// тип 'максимум мощности по тарифам'
typedef struct
{
  maximum       mpmaMax[bTARIFFS];
} power;


// тип 'количество импульсов по тарифам'
typedef struct
{
  ulong         mpdwImp[bTARIFFS];
} impulse;
