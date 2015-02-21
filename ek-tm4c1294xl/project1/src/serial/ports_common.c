/*------------------------------------------------------------------------------
PORTS_COMMON.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "../serial0.h"
#include        "../crc-16.h"
#include        "ports.h"



uchar   InBuff(uint  i) {
  switch (ibPort) {
    case 0: return mpbInBuff0[i];
  }

  return 0; // TODO
}


void    Answer(uint  wSize, serial  seT) {
  switch (ibPort) {
    case 0:	Answer0(wSize, seT); break;
  }
}


uint    IndexInBuff(void) {
  switch (ibPort) {
    case 0: return iwInBuff0;
  }

  return 0; // TODO
}



void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize) {
  switch (ibPort) {
    case 0: MakeCRC16(mpbOutBuff0+bOffset, wSize); break;
  }
}


void    MakeCRC16InBuff(uchar  bOffset, uint  wSize) {
  switch (ibPort) {
    case 0: MakeCRC16(mpbInBuff0+bOffset, wSize); break;
  }
}
