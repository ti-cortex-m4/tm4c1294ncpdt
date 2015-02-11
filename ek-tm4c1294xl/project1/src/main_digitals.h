#include        "main_basic.h"



// тип 'цифровой счётчик'
typedef struct
{
  uchar         ibPort;                 // индекс порта
  uchar         ibPhone;                // индекс телефона
  uchar         bDevice;                // тип электронного счётчика
  uchar         bAddress;               // логический адрес
  uchar         ibLine;                 // вид энергии
} digital;



// тип 'телефона'
typedef struct
{
  uchar         szNumber[bPHONENUMBER+1];
} phone;
