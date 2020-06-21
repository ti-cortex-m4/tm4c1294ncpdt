/*------------------------------------------------------------------------------
ascii_address.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../display/display.h"
#include "ascii_address.h"



void    AsciiAddress_Show(line  *pl) {
  Clear();

  uchar i;
  for (i=0; i<bLINE_SIZE-1; i++) {
    szLo[i] = (*pl).szLine[i];
  }
}



void    AsciiAddress_Init(line  *pl) {
  memset((char *)address, 0, sizeof(line));
  (*pl).szLine[bLINE_SIZE-1] = '0';
}



void    AsciiAddress_Increment(line  *pl, uchar  i) {
  if (((*pl).szLine[i] >= '0') && ((*pl).szLine[i] < '9'))
    (*pl).szLine[i]++;
  else   
    (*pl).szLine[i] = '0';
}


void    AsciiAddress_Decrement(line  *pl, uchar  i) {
  if (((*pl).szLine[i] > '0') && ((*pl).szLine[i] <= '9'))
    (*pl).szLine[i]--;
  else   
    (*pl).szLine[i] = '9';
}



void    AsciiAddress_Enter(line  *pl) {
  uchar i;
  for (i=0; i<bLINE_SIZE-2; i++) {
    (*pl).szLine[i] = (*pl).szLine[i+1];
  } 
  (*pl).szLine[bLINE_SIZE-1] = '0';
}


void    AsciiAddress_Delete(line  *pl) {
  uchar i;
  for (i=0; i<bLINE_SIZE-2; i++) {
    (*pl).szLine[bLINE_SIZE-1-i] = (*pl).szLine[bLINE_SIZE-2-i];
  } 
  (*pl).szLine[0] = 0;
}
