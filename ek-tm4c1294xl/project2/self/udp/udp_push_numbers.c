/*------------------------------------------------------------------------------
udp_push_numbers,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/ustdlib.h"
#include "udp_push_numbers.h"



void PushChar(uchar b);



#define NUMBERS_SIZE    32

static char             mbNumbers[NUMBERS_SIZE];


uint                    cwErrUPDPushNumbersOverflow = 0;



static uchar PushNumberDec(uint w)
{
  memset(&mbNumbers, 0, sizeof(mbNumbers));

  uchar n = usprintf(mbNumbers, "%u" ,w);
  if (n >= NUMBERS_SIZE)
    cwErrUPDPushNumbersOverflow++;

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbNumbers[i]);
  }

  return n;
}



uchar PushCharDec(uchar b)
{
  return PushNumberDec(b);
}


uchar PushIntDec(uint w)
{
  return PushNumberDec(w);
}



static uchar PushNumberHex(uint w)
{
  memset(&mbNumbers, 0, sizeof(mbNumbers));

  uchar n = usprintf(mbNumbers, "%X" ,w);
  if (n >= NUMBERS_SIZE)
    cwErrUPDPushNumbersOverflow++;

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbNumbers[i]);
  }

  return n;
}


uchar PushIntHex(uint w)
{
  return PushNumberHex(w);
}
