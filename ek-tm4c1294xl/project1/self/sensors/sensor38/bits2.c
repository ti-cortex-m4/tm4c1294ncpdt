#include "../../main.h"



unsigned char  *pucDecodeBitArr(unsigned char *pdataout, unsigned char *pdatain) {
  unsigned char  bIn, bOut = 0;
  unsigned int   boId = 0, wiId = 0, woId = 0;

  for (;;) {
    bIn = pdatain[wiId++];
    unsigned char bits;
    for (bits=0; bits<8; bits++) {
      if (bIn & (0x01 << bits)) {
        if (bits != 7)
          bOut |= (0x01 << boId++);
      }
      else {
        if (bits == 7) {
          pdataout[woId] = bOut;
          return &(pdatain[wiId]);
        }
        bOut &= ~(0x01 << boId++);
      }
      if (boId >=8) {
        pdataout[woId++] = bOut;
        bOut = boId = 0;
      }
    }
    if (wiId > 256) break;
  }
  return NUL;
}
