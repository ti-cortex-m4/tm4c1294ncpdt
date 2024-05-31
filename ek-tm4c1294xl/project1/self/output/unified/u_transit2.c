/*------------------------------------------------------------------------------
u_transit2.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "u_transit2.h"



#ifndef MODBUS

void    GetTransit2(void)
{
uint    i;

  for (i=0; i<IndexInBuff()-10; i++) SetInBuff(i, InBuff(i+6));
  SetIndexInBuff(IndexInBuff()-10);

  mpSerial[ibPort] = SER_POSTINPUT_SLAVE;
}

#endif
