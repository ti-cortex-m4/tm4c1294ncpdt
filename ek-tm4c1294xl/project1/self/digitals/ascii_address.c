/*------------------------------------------------------------------------------
ascii_address.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "ascii_address.h"



void    AsciiAddress_Show(line  address) {
{
  uchar i;
  for (i=0; i<bLINE_SIZE-1; i++) {
    Lo[i] = address.szLine[i];  
  }
}



void    AsciiAddress_Init(line  address) {
  memset((char *)address, 0, sizeof(address));
  address.szLine[bLINE_SIZE-1] = '0';
}



void    AsciiAddress_Increment(line  address, uchar  i) {
  if ((address.szLine[i] >= '0') && (address.szLine[i] < '9'))
    address.szLine[i]++;
  else   
    address.szLine[i] = '0';
}


void    AsciiAddress_Decrement(line  address, uchar  i) {
  if ((address.szLine[i] > '0') && (address.szLine[i] <= '9'))    
    address.szLine[i]--;
  else   
    address.szLine[i] = '9';
}



void    AsciiAddress_Enter(line  address) {
  uchar i;
  for (i=0; i<bLINE_SIZE-2; i++) {
    address.szLine[i] = address.szLine[i+1];  
  } 
  address.szLine[bLINE_SIZE-1] = '0';
}


void    AsciiAddress_Delete(line  address) {
  uchar i;
  for (i=0; i<bLINE_SIZE-2; i++) {
    address.szLine[bLINE_SIZE-1-i] = address.szLine[bLINE_SIZE-2-i];  
  } 
  address.szLine[0] = 0;
}
