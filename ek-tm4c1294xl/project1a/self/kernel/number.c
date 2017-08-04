/*------------------------------------------------------------------------------
NUMBER,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "number.h"



uint    AbsInt(sint  w)
{
  return (w < 0) ? -w : w;
}


ulong   AbsLong(slong  dw)
{
  return (dw < 0) ? -dw : dw;
}
