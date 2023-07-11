/*------------------------------------------------------------------------------
MAIN_DIGITALS,H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// цифровой счётчик
typedef struct
{
  uchar         ibPort;                 // индекс порта
  uchar         ibPhone;                // индекс телефона
  uchar         bDevice;                // тип электронного счётчика
  uchar         bAddress;               // логический адрес
  uchar         ibLine;                 // вид энергии
} digital;



// строка текста
typedef struct
{
  char          szLine[bLINE_SIZE+1];
} line;



// вид опроса счётчиков
typedef enum
{
  EXT_PROFILE_30MIN,
  EXT_CURRENT_3MIN,
  EXT_PROFILE_CHECKUP
} extended;



// режим опроса профилей счетчика Меркурий-230
typedef enum
{
  P2M_AUTOMATIC     = 0,
  P2M_SIZE_1        = 1,
  P2M_SIZE_16       = 2,
  P2M_SIZE_17       = 3,
  P2M_BY_DIGITAL    = 4
} profile2mode;
