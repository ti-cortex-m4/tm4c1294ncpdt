/*------------------------------------------------------------------------------
automatic38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../sensors/automatic1.h"
#include "../../time/delay.h"
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


  dbKpulse = 10000;                     // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);     // сохранение К преобразования и К трансформации

  return true;
}
