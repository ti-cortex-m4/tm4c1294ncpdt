#include "../../main.h"



unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn) {
  unsigned char  bIn, bOut = 0;
  unsigned int   boId = 0, i = 0, o = 0;

  for (;;) {
    bIn = pIn[i++];

    uchar t;
    for (t=0; t<8; t++) {
      if (bIn & (0x01 << t)) {
        if (t != 7)
          bOut |= (0x01 << boId++);
      }
      else {
        if (t == 7) {
          pOut[o] = bOut;
          return i; //&(pIn[i]);
        }
        bOut &= ~(0x01 << boId++);
      }
      if (boId >=8) {
        pOut[o++] = bOut;
        bOut = boId = 0;
      }
    }
    if (i > 256) break;
  }
  return 0xFF; //NUL;
}
