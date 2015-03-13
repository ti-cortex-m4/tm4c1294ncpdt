/*------------------------------------------------------------------------------
PORTS_COMMON.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "../memory/mem_serial1.h"
#include        "../memory/mem_serial2.h"
#include        "../memory/mem_serial3.h"
#include        "../isr/serial0.h"
#include        "../isr/serial1.h"
#include        "../isr/serial2.h"
#include        "../isr/serial3.h"
#include        "../crc-16.h"
#include        "ports.h"



uchar   InBuff(uint  i) {
  switch (ibPort) {
    case 0: return mpbInBuff0[i];
    case 1: return mpbInBuff1[i];
    case 2: return mpbInBuff2[i];
    case 3: return mpbInBuff3[i];
  }

  return 0; // TODO
}


void    Answer(uint  wSize, serial  seT) {
  switch (ibPort) {
    case 0:	Answer0(wSize, seT); break;
    case 1:	Answer1(wSize, seT); break;
    case 2:	Answer2(wSize, seT); break;
    case 3:	Answer3(wSize, seT); break;
  }
}


uint    IndexInBuff(void) {
  switch (ibPort) {
    case 0: return iwInBuff0;
    case 1: return iwInBuff1;
    case 2: return iwInBuff2;
    case 3: return iwInBuff3;
  }

  return 0; // TODO
}



void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize) {
  switch (ibPort) {
    case 0: MakeCRC16(mpbOutBuff0 + bOffset, wSize); break;
    case 1: MakeCRC16(mpbOutBuff1 + bOffset, wSize); break;
    case 2: MakeCRC16(mpbOutBuff2 + bOffset, wSize); break;
    case 3: MakeCRC16(mpbOutBuff3 + bOffset, wSize); break;
  }
}


void    MakeCRC16InBuff(uchar  bOffset, uint  wSize) {
  switch (ibPort) {
    case 0: MakeCRC16(mpbInBuff0 + bOffset, wSize); break;
    case 1: MakeCRC16(mpbInBuff1 + bOffset, wSize); break;
    case 2: MakeCRC16(mpbInBuff2 + bOffset, wSize); break;
    case 3: MakeCRC16(mpbInBuff3 + bOffset, wSize); break;
  }
}
