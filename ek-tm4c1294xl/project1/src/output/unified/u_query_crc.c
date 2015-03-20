/*------------------------------------------------------------------------------
U_QUERY_CRC.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "ports.h"
#include        "ports2.h"
#include        "postinput.h"



#ifndef MODBUS

void    GetQueryCRCUni(void) 
{
uint    i;

  for (i=0; i<IndexInBuff()-10; i++) SetInBuff(i, GetInBuff(i+6));
  SetIndexInBuff(IndexInBuff()-10);

  mpSerial[ibPort] = SER_POSTINPUT_SLAVE;
}

#endif
*/
