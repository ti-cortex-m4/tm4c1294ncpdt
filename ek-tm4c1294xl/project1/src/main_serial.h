#include        "main_basic.h"



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
