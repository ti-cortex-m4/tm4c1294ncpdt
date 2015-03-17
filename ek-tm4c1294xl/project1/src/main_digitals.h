/*------------------------------------------------------------------------------
MAIN_DIGITALS.H


------------------------------------------------------------------------------*/

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



// тип 'номер телефона'
typedef struct
{
  char          szNumber[bPHONENUMBER+1];
} phone;



// тип 'вид опроса счётчиков'
typedef enum
{
  EXT_PROFILE_30MIN,
  EXT_CURRENT_3MIN,
  EXT_PROFILE_CHECKUP
} extended;
