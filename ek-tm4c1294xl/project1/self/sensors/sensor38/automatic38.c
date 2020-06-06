/*------------------------------------------------------------------------------
automatic38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../sensors/automatic1.h"
#include "../../hardware/beep.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "device38.h"
#include "io38.h"
#include "automatic38.h"



bool    Automatic38(void)
{
  Clear();

  QuerynNumber38();
  if (Input38() != SER_GOODCHECK) return false;

  ShowLong(ReadNumber38());
  Delay(1000);


  dbKpulse = 1000;                      // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);     // сохранение К преобразования и К трансформации

  return true;
}



bool    ChangeSpeed38(void)
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

  ShowLong(ReadNumber38());
  return true;
}
