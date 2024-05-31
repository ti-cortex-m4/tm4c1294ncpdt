/*------------------------------------------------------------------------------
U_QUERY_CRC!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "u_query_crc.h"



#ifndef MODBUS

void    GetQueryCRCUni(void) 
{
uint    i;

  for (i=0; i<IndexInBuff()-10; i++) SetInBuff(i, InBuff(i+6));
  SetIndexInBuff(IndexInBuff()-10);

  mpSerial[ibPort] = SER_POSTINPUT_SLAVE;
}

#endif
