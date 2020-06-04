/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dff.h"

#include "../../serial/monitor.h"


int EncodeInt(int64_t value, uint8_t *send_buffer_position) {
  int num=0; // число записанных байт (лбф + 7 бит)
  char ch;

  //условие остановки кодирования: оставшиеся биты и последний записанный либо нули либо единицы
  while ((value>>(num*7-1)) != -1 && (value>>(num*7-1)) != 0 || num==0) {
    ch = (char)(value>>(num*7));                         // следующие 7 бит
    *send_buffer_position++ = ch | 0x80;                  // запись с флагом lbf
    num++; //записали очередные 7 бит
  }
  *(send_buffer_position-1) &= 0x7F;                      //убрать флаг у последнего байта
  return num;
}



uchar   DffEncode(int64_t  dwValue, uchar*  pbOut) {
  int num = 0; // число записанных байт (лбф + 7 бит)
  int bits = 0;

  while (true)
  {
    int64_t new = dwValue >> (bits - 1);
    bool f1 = (new != -1);
    bool f2 = (new != 0);
    bool f3 = (num == 0);
    bool f = ((f1 && f2) || f3);
    if (f == false) break; // условие остановки кодирования: оставшиеся биты и последний записанный либо нули либо единицы

    char ch = (char)(dwValue >> bits); // следующие 7 бит

    *pbOut++ = ch | 0x80; // запись с флагом lbf
    num++;
    bits += 7; // записали очередные 7 бит
  }

  *(pbOut - 1) &= 0x7F; //убрать флаг у последнего байта
  return num;
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



uchar*      DffDecode(uchar  *pbIn, int64_t  *pdwOut) {
  int bits = 0;
  uint64_t ch;

  do {
    ch = (*pbIn & 0x7F);
    (*pdwOut) += (ch << bits);
    bits += 7;
  }
  while (*(pbIn++) & 0x80);

  if (ch >> 6)
    (*pdwOut) |= (0xffffffffffffffff << bits);

  return pbIn;
}



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
