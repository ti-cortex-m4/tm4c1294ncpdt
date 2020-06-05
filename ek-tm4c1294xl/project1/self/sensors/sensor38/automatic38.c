/*------------------------------------------------------------------------------
automatic38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../sensors/automatic1.h"
#include "automatic38.h"



bool    Automatic38(void)
{
  Clear();

  dbKpulse = 10000         ;            // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);     // сохранение К преобразования и К трансформации

  return true;
}
