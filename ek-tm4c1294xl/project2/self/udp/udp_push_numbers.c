/*------------------------------------------------------------------------------
udp_push_numbers.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/ustdlib.h"
#include "udp_push_numbers.h"



void PushChar(uchar b);



#define NUMBERS_SIZE    32

static char             mbNumbers[NUMBERS_SIZE];


uint                    cwErrUPDPushNumbersOverflow = 0;



static uchar PushNumber(const char *pcszFormat, const uint w)
{
  memset(&mbNumbers, 0, sizeof(mbNumbers));

  uchar n = usprintf(mbNumbers, pcszFormat ,w);
  if (n >= NUMBERS_SIZE)
  {
    cwErrUPDPushNumbersOverflow++;
  }

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbNumbers[i]);
  }

  return n;
}


static uchar PushNumberDec(const uint w)
{
  return PushNumber("%u", w);
}


static uchar PushNumberHex(const uint w)
{
  return PushNumber("%X", w);
}



uchar PushCharDec(const uchar b)
{
  return PushNumberDec(b);
}


uchar PushIntDec(const uint w)
{
  return PushNumberDec(w);
}


uchar PushIntHex(const uint w)
{
  return PushNumberHex(w);
}
