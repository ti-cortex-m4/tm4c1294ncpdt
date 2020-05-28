/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dff.h"



void left_shift2(uchar  *array, uint  wSize, uint  bits)
{
  uint b;
  for (b=0; b<bits; b++)
  {
    sint i;
    for (i=wSize-1; i >= 0; i--)
    {
      array[i] = array[i] << 1;

      if (i > 0)
      {
        uchar c = (array[i-1] >> 7) & 0x01;
        array[i] = array[i] | c;
      }
    }
  }
}


uchar*  DffPopDecodeBuff(uchar  i) {
  static uchar result[1000];
  uchar buff[1000];

  InitPop(i);

  memset(&result, 0, sizeof(result));
  int bits = 0;

  do {
    memset(&buff, 0, sizeof(buff));
    buff[0] = (InBuff(i) & 0x7F);

    left_shift2(buff, sizeof(buff), bits);

    uint i;
    for (i=0; i < sizeof(result); i++)
      result[i] |= buff[i];

    bits += 7;
  }
  while (InBuff(i++) & 0x80);

  return result;
}



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
