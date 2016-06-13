/*------------------------------------------------------------------------------
udp_push_numbers,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/ustdlib.h"
#include "udp_push_numbers.h"



void PushChar(uchar b);



#define PUSH_SIZE       32

static char             mbPush[PUSH_SIZE];


uint                    cwErrUPDPushNumbersOverflow = 0;



uchar PushCharDec(uchar b)
{
  memset(&mbPush, 0, sizeof(mbPush));

  uchar n = usprintf(mbPush, "%u" ,b);
  if (n >= PUSH_SIZE)
    cwErrUPDPushNumbersOverflow++;

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbPush[i]);
  }

  return n;
}


uchar PushIntDec(uint w)
{
  memset(&mbPush, 0, sizeof(mbPush));

  uchar n = usprintf(mbPush, "%u" ,w);
  if (n >= PUSH_SIZE)
    cwErrUPDPushNumbersOverflow++;

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbPush[i]);
  }

  return n;
}


uchar PushIntHex(uint w)
{
  memset(&mbPush, 0, sizeof(mbPush));

  uchar n = usprintf(mbPush, "%X" ,w);
  if (n >= PUSH_SIZE)
    cwErrUPDPushNumbersOverflow++;

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbPush[i]);
  }

  return n;
}
