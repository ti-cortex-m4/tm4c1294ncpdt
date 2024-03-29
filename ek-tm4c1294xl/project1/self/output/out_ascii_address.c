/*------------------------------------------------------------------------------
out_ascii_address.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../digitals/digitals.h"
#include "../digitals/address/ascii_address.h"
#include "../nvram/cache.h"
#include "out_ascii_address.h"



void    OutGetAsciiAddress(void)
{
  if (bInBuff6 < bCANALS)
  {
    InitPushCRC();
    PushLongBig(mpdwAddress1[bInBuff6]);
    Push(&mpphAsciiAddress[bInBuff6], sizeof(line));
    Output(sizeof(ulong) + sizeof(line));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetAsciiAddress(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff6 < bCANALS)
    {
      InitPop(7);
      mpdwAddress1[bInBuff6] = PopLongBig();

      uchar i;
      for (i=0; i<bLINE_SIZE; i++)
        mpphAsciiAddress[bInBuff6].szLine[i] = PopChar();

      if (bInBuff6 == bCANALS - 1)
      {
        SaveCache(&chAddress1);
        SaveCache(&chAsciiAddress);
      }

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutGetAsciiAddressesExt(void)
{
  InitPushPtr();
  uchar wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushLongBig(mpdwAddress1[c]);
      wSize += sizeof(ulong);

      Push(&mpphAsciiAddress[c], sizeof(line));
      wSize += sizeof(line);
    }
  }

  OutptrOutBuff(wSize);
}
