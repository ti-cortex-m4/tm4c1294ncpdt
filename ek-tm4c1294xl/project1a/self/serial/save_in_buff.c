/*------------------------------------------------------------------------------
SAVEBUFF!C


-----------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_serial0.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_serial2.h"
#include "../memory/mem_serial3.h"
#include "../memory/mem_ports.h"
#include "ports.h"



void    SaveInBuff(void)
{
  switch (ibPort)
  {
    case 0:  memcpy(mpbInBuffSave, mpbInBuff0, wINBUFF_SIZE);  break;
    case 1:  memcpy(mpbInBuffSave, mpbInBuff1, wINBUFF_SIZE);  break;
    case 2:  memcpy(mpbInBuffSave, mpbInBuff2, wINBUFF_SIZE);  break;
    case 3:  memcpy(mpbInBuffSave, mpbInBuff3, wINBUFF_SIZE);  break;
    default: ASSERT(false);
  }
}



void    InitPopSave(uint  i)
{
  iwPopSave = i;
}


uchar   PopCharSave(void)
{
  return( mpbInBuffSave[ iwPopSave++ ] ); 
}

