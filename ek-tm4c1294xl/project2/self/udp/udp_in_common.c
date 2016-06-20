/*------------------------------------------------------------------------------
udp_in_common.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_pop.h"
#include "udp_in_common.h"



bool IsCmd(struct pbuf *p, const char *pcszCmd)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (*pcszCmd)
  {
    if (i >= p->len)
      return false;

    if (pb[i++] != *pcszCmd++)
      return false;
  }

  return true;
}


uchar2 GetCmdEndIndex(struct pbuf *p, const char *pcszCmd)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (*pcszCmd)
  {
    if (i >= p->len)
    {
      return GetChar2Error();
    }

    if (pb[i++] != *pcszCmd++)
    {
      return GetChar2Error();
    }
  }

  return GetChar2Success(i);
}


uchar2 GetBorderIndex(struct pbuf *p, uchar bBorder)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (true)
  {
    if (i >= p->len)
    {
      return GetChar2Error();
    }

    if (pb[i++] == bBorder)
    {
      return GetChar2Success(i);
    }
  }
}
