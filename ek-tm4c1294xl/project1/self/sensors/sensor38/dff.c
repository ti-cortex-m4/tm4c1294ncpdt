/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dff.h"



uint64_t DffPopDecodeLong64(uchar  i) {
  InitPop(i);

  uint64_t result = 0;
  int bits = 0;
  uint64_t ddw;

  do {
    ddw = (InBuff(i) & 0x7F);
    result += (ddw << bits);
    bits += 7;
  }
  while (InBuff(i++) & 0x80);

//  if (ddw >> 6)
//    result |= (0xffffffffffffffff << bits);

  return result;
}



uint64_t DffDecodeLong64(uchar  *pb) {
  uint64_t result = 0;
  int bits = 0;
  uint64_t ddw;

  do {
    ddw = (*pb & 0x7F);
    result += (ddw << bits);
    bits += 7;
  }
  while (*(pb++) & 0x80);

//  if (ddw >> 6)
//    result |= (0xffffffffffffffff << bits);

  return result;
}



ulong   DffDecodeLong(uchar  *pb) {
  ulong result = 0;
  int bits = 0;
  ulong dw;

  do {
    dw = (*pb & 0x7F);
    result += (dw << bits);
    bits += 7;
  }
  while (*(pb++) & 0x80);

//  if (dw >> 6)
//    result |= (0xffffffff << bits);

  return result;
}
