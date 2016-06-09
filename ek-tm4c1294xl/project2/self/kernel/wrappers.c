/*------------------------------------------------------------------------------
wrappers.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "wrappers.h"



uchar GetChar2(uchar  w, err_t  err);
{
  uchar dw;

  dw.dw = dw;
  dw.err = err;

  return dw;
}


uchar  GetChar2Error(void)
{
  return GetChar2(MAX_CHAR, ERR_VAL);
}

uint GetInt2(uint  w, err_t  err);
{
  uint dw;

  dw.dw = dw;
  dw.err = err;

  return dw;
}


uint  GetInt2Error(void)
{
  return GetInt2(MAX_INT, ERR_VAL);
}



ulong2 GetLong2(ulong  dw, err_t  err);
{
  ulong2 dw2;

  dw2.dw = dw;
  dw2.err = err;

  return dw2;
}


ulong2  GetLong2Error(void)
{
  return GetLong2(MAX_LONG, ERR_VAL);
}
