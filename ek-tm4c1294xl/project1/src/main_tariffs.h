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
} zones;


// тип 'мощность/энергия'
typedef enum
{
  DOM_POWER,
  DOM_ENERGY
} domain;


// тип 'период задания тарифов'
typedef enum
{
  PER_INIT              = 0,
  PER_MONTH             = 1,
  PER_QUARTER           = '-',
  PER_YEAR              = '_',
} period;


// тип 'список праздников'
typedef struct
{
  uchar         bSize;                  // количество праздников
  time          mptiDate[bRELAXS];      // даты праздников
} relaxs;


// тип 'излом тарифного периода'
typedef struct
{
  uchar         bSize;                  // количество изломов
  time          mptiDate[bGAPS]  ;      // даты изломов (секунда - номер псевдо-месяца)
} gaps;
