/*------------------------------------------------------------------------------
PORTS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_ports.h"
#include        "memory/mem_settings.h"
#include        "memory/mem_serial0.h"
#include        "memory/mem_realtime.h"
#include        "include/queries.h"
#include        "crc-16.h"
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

  PushChar( 0/*GetHouIndex()*/ );
  PushChar( 0/*mpibEngCurrTariff[ GetHouIndex() ]*/ );
  PushChar( 0/*mpibPowCurrTariff[ GetHouIndex() ]*/ );

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
  }

  Answer(wSize+bHEADER,SER_HEADER);
}


void    OutptrOutBuff(uint  wSize) {
  switch (ibPort) {
    case 0:  Outptr(&mpbOutBuff0[bHEADER], wSize);  break;
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
