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

uchar   EncodeInt_(uchar*  send_buffer_position, int64_t  value) {
  int num = 0; // число записанных байт (лбф + 7 бит)
  int bits = 0;
  // char ch;

  while (true) //условие остановки кодирования: оставшиеся биты и последний записанный либо нули либо едини
  {
    MonitorString("\n ");
    int64_t new = value >> (bits - 1);
    UARTprintf("%X ", new % 0x100000000);

    bool f1 = (new != -1);
    bool f2 = (new != 0);
    bool f3 = (num == 0);
    bool f = ((f1 && f2) || f3);
    MonitorBool(f1);
    MonitorBool(f2);
    MonitorBool(f3);
    MonitorBool(f);

    if (f == false) break;

//    MonitorString("\n a="); MonitorIntHex(value >> (bits - 1));
    // if (send_buffer_position > send_buffer + PACKETMAXSIZE) // если вышли за пределы пакета отменить операцию
    // {
    //   send_buffer_position -= num;
    //   return 1;
    // }
    uchar ch = (uchar)(value >> bits); // следующие 7 бит
    MonitorString(" x="); MonitorCharHex(ch);

    *send_buffer_position++ = ch | 0x80; // запись с флагом lbf
    num++; //записали очередные 7 бит
    bits += 7;
  }

  *(send_buffer_position - 1) &= 0x7F; //убрать флаг у последнего байта
  MonitorString("\n num="); MonitorCharHex(num);
   return num;
}


/*
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


uchar*  DffPopDecodeBuff(uchar  *pb) {
  static uchar result[8];
  uchar buff[8];

//  InitPop(i);

  memset(&result, 0, sizeof(result));
  int bits = 0;

  do {
    memset(&buff, 0, sizeof(buff));
    buff[0] = (*pb / *InBuff(i)* / & 0x7F);

    left_shift2(buff, sizeof(buff), bits);

    uint i;
    for (i=0; i < sizeof(result); i++)
      result[i] |= buff[i];

    bits += 4/ *7* /;
  }
  while (*(pb++)/ *InBuff(i++)* / & 0x80);

  return result;
}
*/


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

uchar*  DffDecodeLong64_(uchar  *pb, int64_t  *pOut) {
//  uint64_t result = 0;
  int bits = 0;
  uint64_t ddw;

  do {
    ddw = (*pb & 0x7F);
    (*pOut) += (ddw << bits);
    bits += 7;
  }
  while (*(pb++) & 0x80);

  if (ddw >> 6)
    (*pOut) |= (0xffffffffffffffff << bits);

  return pb;
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
