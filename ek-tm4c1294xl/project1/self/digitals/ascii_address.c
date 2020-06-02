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
  memset((char *)AsciiAddress, 0, sizeof(AsciiAddress));
  AsciiAddress.szLine[bLINE_SIZE] = '0';
}



void    AsciiAddress_Increment(line  address, uchar  i) {
  if (AsciiAddress.szLine[i] < '9')    
    AsciiAddress.szLine[i]++;
  else   
    AsciiAddress.szLine[i] = '0';
}


void    AsciiAddress_Decrement(line  address, uchar  i) {
  if (AsciiAddress.szLine[i] > '0')    
    AsciiAddress.szLine[i]--;
  else   
    AsciiAddress.szLine[i] = '9';
}



void    AsciiAddress_Enter(line  address) {
  uchar i;
  for (i=0; i<bLINE_SIZE-1; i++) {
    AsciiAddress.szLine[i] = AsciiAddress.szLine[i+1];  
  } 
  AsciiAddress.szLine[bLINE_SIZE] = '0';
}


void    AsciiAddress_Delete(line  address) {
  uchar i;
  for (i=0; i<bLINE_SIZE-1; i++) {
    AsciiAddress.szLine[bLINE_SIZE-i] = AsciiAddress.szLine[bLINE_SIZE-i-1];  
  } 
}
