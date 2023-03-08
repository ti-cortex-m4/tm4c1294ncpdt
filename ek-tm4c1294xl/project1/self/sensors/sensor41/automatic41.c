/*------------------------------------------------------------------------------
automatic41.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../sensors/automatic1.h"
#include "../../hardware/beep.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "device41.h"
#include "../sensor38/io38.h"
#include "automatic41.h"



bool    Automatic41(void)
{
  Clear();

  QueryNumber41();
  if (Input38() != SER_GOODCHECK) return false;

  ShowLong(ReadNumber41());
  Delay(1000);


  dbKpulse = 1000;                      // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);     // сохранение К преобразования и К трансформации

  return true;
}



bool    ChangeSpeed41(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushLongLtl(0);

  PushChar(0x00);
  PushChar(0x06);

  PushChar(6);
  PushChar(0);
  PushChar(5);

  Query38(250, 14);


  if (Input38() != SER_GOODCHECK) return false;
  Beep();

  ShowLong(ReadNumber41());
  return true;
}
