#include        "main_basic.h"



// тип 'состояния клавиатуры'
typedef enum
{
  KBD_BEGIN,
  KBD_PROGRAM,
  KBD_DIGITS,
  KBD_ENTER,
  KBD_POSTENTER,
  KBD_INPUT1,
  KBD_POSTINPUT1,
  KBD_INPUT2,
  KBD_POSTINPUT2,
  KBD_INPUT3,
  KBD_POSTINPUT3,
  KBD_INPUT4,
  KBD_POSTINPUT4,
  KBD_INPUT5,
  KBD_POSTINPUT5,
  KBD_INPUT6,
  KBD_POSTINPUT6,
  KBD_SHOW,
  KBD_POSTSHOW
} key;


// коды кнопок
#define bARR_UP         8
#define bARR_DOWN       2
#define bARR_LEFT       4
#define bARR_RIGHT      6
#define bARR_PGUP       9
#define bARR_PGDN       3
#define bARR_HOME       7
#define bARR_END        1

#define bKEY_MINUS      10
#define bKEY_POINT      11
#define bKEY_PROGRAM    12
#define bKEY_ENTER      13
