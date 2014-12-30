#ifndef __MAIN
#define __MAIN


#include        <stdint.h>
#include        <stdbool.h>
#include        "system.h"
#include        "main_keyboard.h"
#include        "main_serial.h"


typedef unsigned char   uchar;
typedef signed char     schar;

typedef unsigned int    uint;
typedef signed int      sint;

typedef unsigned long   ulong;
typedef signed long     slong;


// тип 'строка сообщения'
typedef uchar           message[bDISPLAY+1];


// тип 'время и дата'
typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
  uchar         bDay;
  uchar         bMonth;
  uchar         bYear;
} time;


typedef enum
{
  boFalse               = 0x00,
  boTrue                = 0xFF
} boolean;


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


// тип 'сострежим работы прибора'
typedef enum
{
  GLB_PROGRAM           = 0,
  GLB_WORK              = 1,
  GLB_REPROGRAM         = 2
} global;


// тип 'настройки порта'
typedef struct
{
  uchar         ibSpeed;                // индекс скорости
  uchar         ibParity;               // индекс контроля чётности
  stream        enStream;               // режим работы порта
} port;


#endif






