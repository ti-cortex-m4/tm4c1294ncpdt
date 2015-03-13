/*------------------------------------------------------------------------------
PORTS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_serial0.h"
#include        "../memory/mem_serial1.h"
#include        "../memory/mem_serial2.h"
#include        "../memory/mem_serial3.h"
#include        "../memory/mem_realtime.h"
#include        "../include/queries.h"
#include        "../realtime/realtime.h"
#include        "../crc-16.h"
#include        "ports_stack.h"
#include        "ports_common.h"



serial 					mpSerial[bPORTS];

uchar                   ibPort;



void    Output(uint  wSize) {
  InitPush(0);

  PushChar(bLogical);
  PushChar(0);

  PushChar( (wSize+7) % 0x100 );
  PushChar( (wSize+7) / 0x100 );

  PushChar(bQuery);

  MakeCRC16OutBuff(0,wSize+5);
  Skip(wSize);

  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Answer(wSize+7,SER_OUTPUT_SLAVE);
}


void    Result(uchar  bT) {
  InitPushCRC();
  PushChar(bT);

  Output(1);
}


void    LongResult(uchar  bT) {
  InitPushCRC();
  PushChar(bT);
  PushChar(0);

  Output(2);
}


void    Outptr(void  *pData, uint  wSize)
{
  InitPush(0);

  PushChar(bLogical);
  PushChar(0);

  PushChar( (bHEADER + wSize + 2) % 0x100 );
  PushChar( (bHEADER + wSize + 2) / 0x100 );

  PushChar(bQuery);

  InitPushCRC();

  PushChar( GetCurrHouIndex() );
  PushChar( mpibEngCurrTariff[ GetCurrHouIndex() ] );
  PushChar( mpibPowCurrTariff[ GetCurrHouIndex() ] );

  PushChar(ibSoftMnt);
  PushInt(iwHardHou);
  PushChar(ibHardDay);
  PushChar(ibHardMon);

  PushChar(0/*cbWaitQuery*/);
  PushChar(0);

  MakeCRC16OutBuff(0,bHEADER);

  switch (ibPort)
  {
    case 0:
      pbData0 = pData;
      bCRCHi0 = bCRCHi;
      bCRCLo0 = bCRCLo;
      break;

    case 1:
      pbData1 = pData;
      bCRCHi1 = bCRCHi;
      bCRCLo1 = bCRCLo;
      break;

    case 2:
      pbData2 = pData;
      bCRCHi2 = bCRCHi;
      bCRCLo2 = bCRCLo;
      break;

    case 3:
      pbData3 = pData;
      bCRCHi3 = bCRCHi;
      bCRCLo3 = bCRCLo;
      break;
  }

  Answer(wSize+bHEADER,SER_HEADER);
}


void    OutptrOutBuff(uint  wSize) {
  switch (ibPort) {
    case 0:  Outptr(&mpbOutBuff0[bHEADER], wSize);  break;
    case 1:  Outptr(&mpbOutBuff1[bHEADER], wSize);  break;
    case 2:  Outptr(&mpbOutBuff2[bHEADER], wSize);  break;
    case 3:  Outptr(&mpbOutBuff3[bHEADER], wSize);  break;
  }
}


void    Common(void  *pbData, uint  wSize) {
  if (5+wSize < wOUTBUFF_SIZE-bMARGIN) {
    InitPushCRC();
    Push(pbData, wSize);
    Output(wSize);
  }
  else Result(bRES_OUTOVERFLOW);
}
