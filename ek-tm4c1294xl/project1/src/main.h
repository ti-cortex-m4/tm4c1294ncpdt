#ifndef __MAIN
#define __MAIN


#include        <stdint.h>
#include        <stdbool.h>
#include        "system.h"
#include        "main_keyboard.h"


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


// тип 'режим работы порта'
typedef enum 
{ 
  STR_SLAVEESC          = 0,
  STR_SLAVECRC          = 1,
  STR_MASTERDIRECT      = 2,
  STR_MASTERMODEM       = 3,
  STR_SLAVEUNI          = 4
} stream;


// тип 'настройки порта'
typedef struct
{
  uchar         ibSpeed;                // индекс скорости
  uchar         ibParity;               // индекс контроля чётности
  stream        enStream;               // режим работы порта
} port;



// тип 'состояние порта'
typedef enum 
{ 
  SER_BEGIN             = 0,            // начальное состояние

  SER_OUTPUT_SLAVE      = 1,            // передача
  SER_INPUT_SLAVE       = 2,            // приём
  SER_POSTINPUT_SLAVE   = 3,            // приём завершён

  SER_HEADER            = 4,            // передача заголовка
  SER_POINTER           = 5,            // передача данных по указателю
  SER_CRCLO             = 6,            // передача младнего байта CRC
  SER_CRCHI             = 7,            // передача старшего байта CRC
  SER_CLOSE             = 8,            // передача завершена

  SER_ESC               = 9,            // приём Esc
  SER_CTRL_Z            = 10,           // приём Ctrl Z
  SER_CHAR              = 11,           // приём символа

  SER_OUTPUT_MASTER     = 20,           // передача
  SER_INPUT_MASTER      = 21,           // приём
  SER_POSTINPUT_MASTER  = 22,           // приём завершён

  SER_ANSWER_MODEM      = 23,           // приём от модема
  SER_POSTANSWER_MODEM  = 24,           // приём от модема завершён

  SER_GOODCHECK         = 30,           // контрольная сумма совпадает
  SER_BADCHECK          = 31,           // ошибка: плохая контрольная сумма
  SER_BADLINK           = 32,           // ошибка: нет ответа
  SER_OVERFLOW          = 33,           // ошибка: переполнение входного буфера

  SER_PAUSE             = 40,           // пауза отработана

  SER_PACKET_HEADER     = 50,
  SER_PACKET_BODY       = 51,

  SER_LOCAL             = 60,
  SER_BULK              = 61,

  SER_INPUT_SLAVE2      = 62,           // приём
  SER_POSTINPUT_SLAVE2  = 63,           // приём завершён
} serial;        


#define SERIAL_MODEM    0xFF00
#define SERIAL_LOCAL    0xFF01


#endif






