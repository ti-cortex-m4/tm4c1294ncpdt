/*------------------------------------------------------------------------------
PORTS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_ports.h"
#include        "mem_settings.h"
#include        "mem_serial0.h"
#include        "queries.h"
#include        "crc-16.h"
#include        "ports_stack.h"
#include        "ports_common.h"



serial 					mpSerial[bPORTS];

uchar                   ibPort;



void    Output(uint  wSize) {
  InitPush();

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


void    Common(void  *pbData, uint  wSize) {
  if (5+wSize < wOUTBUFF_SIZE-bMARGIN) {
    InitPushCRC();
    Push(pbData, wSize);
    Output(wSize);
  }
  else Result(bRES_OUTOVERFLOW);
}
