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



void    AsciiAddress_Increment(line  *pl) {
  uchar i = strlen((char const *)(*pl).szLine);
  sprintf(szHi,"%u",i);
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
  sprintf(szHi,"%u",i);
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



void    AsciiAddress_Enter(line  *pl, uchar  idx) {
  uchar i;
  for (i=idx; i>0; i--) {
    (*pl).szLine[i] = (*pl).szLine[i-1];
  } 
  (*pl).szLine[0] = '0';
}


void    AsciiAddress_Delete(line  *pl, uchar  idx) {
  uchar i;
  for (i=0; i<idx; i++) {
    (*pl).szLine[i] = (*pl).szLine[i+1];
  } 
  (*pl).szLine[idx] = 0;
}
