#include "../../main.h"



unsigned char  pucDecodeBitArr(unsigned char pdataout, unsigned char *pdatain) {
  unsigned char  in_data, out_data = 0;
  MdUns            boId = 0, wiId = 0, woId = 0;

  for (;;) {
    in_data = pdatain[wiId++];
    for (MdUns biId=0; biId<8; biId++) {
      if (in_data & (0x01 << biId)) {
        if (biId != 7)
          out_data |= (0x01 << boId++);
      }
      else {
        if (biId == 7) {
          pdataout[woId] = out_data;
          return &(pdatain[wiId]);
        }
        out_data &= ~(0x01 << boId++);
      }
      if (boId >=8) {
        pdataout[woId++] = out_data;
        out_data = boId = 0;
      }
    }
    if (wiId > 256) break;
  }
  return NUL;
}
