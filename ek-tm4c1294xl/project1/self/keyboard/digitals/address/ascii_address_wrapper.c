/*------------------------------------------------------------------------------
ascii_address_wrapper.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../display/display.h"
#include "ascii_address_wrapper.h"



void    AsciiAddress_Show(line  *pl) {
  sprintf(szLo+4,"%12s",(*pl).szLine);
}


void    AsciiAddress_Init(line  *pl) {
  memset((char *)pl, 0, sizeof(line));
}


uchar   AsciiAddress_Size(line  *pl) {
  return strlen((char const *)(*pl).szLine);
}



void    AsciiAddress_Increment(line  *pl) {
  uchar i = strlen((char const *)(*pl).szLine);
  if (i > 0) i--;

  if ((*pl).szLine[i] == 'Z')
    (*pl).szLine[i] = '0';
  else if ((*pl).szLine[i] == 'z')
    (*pl).szLine[i] = 'A';
  else if ((*pl).szLine[i] >= 'a')
    (*pl).szLine[i]++;
  else if ((*pl).szLine[i] >= 'A')
    (*pl).szLine[i]++;
  else if ((*pl).szLine[i] == '9')
    (*pl).szLine[i] = 'a';
  else if ((*pl).szLine[i] >= '0')
    (*pl).szLine[i]++;
  else   
    (*pl).szLine[i] = '0';
}


void    AsciiAddress_Decrement(line  *pl) {
  uchar i = strlen((char const *)(*pl).szLine);
  if (i > 0) i--;

  if ((*pl).szLine[i] == '0')
    (*pl).szLine[i] = 'Z';
  else if ((*pl).szLine[i] <= '9')
    (*pl).szLine[i]--;
  else if ((*pl).szLine[i] == 'A')
    (*pl).szLine[i] = 'z';
  else if ((*pl).szLine[i] <= 'Z')
    (*pl).szLine[i]--;
  else if ((*pl).szLine[i] == 'a')
    (*pl).szLine[i] = '9';
  else if ((*pl).szLine[i] <= 'z')
    (*pl).szLine[i]--;
  else
    (*pl).szLine[i] = 'Z';
}



void    AsciiAddress_Enter(line  *pl) {
  uchar s = strlen((char const *)(*pl).szLine);
  (*pl).szLine[s] = '0';
}


void    AsciiAddress_Delete(line  *pl) {
  uchar s = strlen((char const *)(*pl).szLine);
  (*pl).szLine[s-1] = 0;
}
