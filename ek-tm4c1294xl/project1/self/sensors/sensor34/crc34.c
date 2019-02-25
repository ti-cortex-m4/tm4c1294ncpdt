/*------------------------------------------------------------------------------
crc34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "crc34.h"



unsigned short MakeCRC34(unsigned short *data, int count) {
  const unsigned long base = 7;

  unsigned long hash = base;
  unsigned long crc = count;

  while (count > 1) {
    crc += hash * (*data++);
    hash *= base;
    count -= 2;
  }

  if (count) {
    crc += *(unsigned char*)data * hash;
  }

  crc *= hash;
  return crc + (crc >> 16);
}
