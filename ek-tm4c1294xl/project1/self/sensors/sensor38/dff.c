/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dff.h"



int     Encode38(int64_t  ddwValue, uchar  *pbOut) {
  int num = 0; // число записанных байт (lbf + 7 бит)
  char ch;

  // условие остановки кодирования: оставшиеся биты и последний записанный либо нули либо единицы
  while ((ddwValue>>(num*7-1)) != -1 && (ddwValue>>(num*7-1)) != 0 || num==0) {
    ch = (char)(ddwValue>>(num*7));                       // следующие 7 бит
    *pbOut++ = ch | 0x80;                                 // запись с флагом lbf
    num++;                                                // записали очередные 7 бит
  }

  *(pbOut-1) &= 0x7F;                                     // убрать флаг lbf у последнего байта
  return num;
}



uchar   DffEncode(int64_t  ddwValue, uchar  *pbOut) {
  int bytes = 0;
  int shift = 0;

  while (true)
  {
    int64_t ddw = ddwValue >> (shift - 1);
    bool f1 = (ddw != -1);
    bool f2 = (ddw != 0);
    bool f3 = (bytes == 0);
    bool f = ((f1 && f2) || f3);
    if (f == false) break; // условие остановки кодирования: оставшиеся биты и последний записанный либо нули либо единицы

    char ch = (char)(ddwValue >> shift); // следующие 7 бит

    *pbOut++ = ch | 0x80; // запись с флагом lbf

    bytes++;
    shift += 7;
  }

  *(pbOut - 1) &= 0x7F; // убрать флаг lbf у последнего байта

  return bytes;
}



uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut) {
  int shift = 0;
  uint64_t ch;

  do {
    ch = (*pbIn & 0x7F);
    (*pdwOut) += (ch << shift);
    shift += 7;
  }
  while (*(pbIn++) & 0x80);

  if (ch >> 6)
    (*pdwOut) |= (0xffffffffffffffff << shift);

  return pbIn;
}


uchar*  DffDecodePositive(uchar  *pbIn, int64_t  *pdwOut) {
  int bits = 0;
  uint64_t ch;

  do {
    ch = (*pbIn & 0x7F);
    (*pdwOut) += (ch << bits);
    bits += 7;
  }
  while (*(pbIn++) & 0x80);

  return pbIn;
}
