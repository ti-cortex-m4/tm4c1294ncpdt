#include        "main_basic.h"



// тип 'излом тарифного графика'
typedef struct
{
  uchar         bHour;                  // час
  uchar         bMinute;                // минуты
  uchar         ibTariff;               // индекс тарифа
} breaks;


// тип 'тарифный график за сутки'
typedef struct
{
  uchar         bSize;                  // количество изломов в тарифном графике
  breaks        mpbrBreaks[bBREAKS];    // изломы тарифного графика
} zone;


// тип 'мощность/энергия'
typedef enum
{
  POWER,
  ENERGY
} domain;


// тип 'период задания тарифов'
typedef enum
{
  NONE          = 0,
  MONTH         = 1,
  QUARTER       = '-',
  YEAR          = '_',
} period;


// тип 'список праздников'
typedef struct
{
  uchar         bSize;                  // количество праздников
  time          mptiDate[bRELAXS];      // даты праздников
} relax;


// тип 'специальные тарифные периоды'
typedef struct
{
  uchar         bSize;                  // количество периодов
  time          mptiDate[bGAPS];        // даты периодов (секунда - номер псевдо-месяца)
} gap;
