/*------------------------------------------------------------------------------
PORTS.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/queries.h"
#include "../include/queries2.h"
#include "ports_stack.h"
#include "ports_common.h"



extern  serial                  mpSerial[bPORTS];

extern  uchar                   ibPort;

extern  uchar                   ibPortPause;

extern  uchar                   bPortsStatus;



void    Output(uint  wSize);
void    Result(uchar  bT);
void    LongResult(uchar  bT);
void    Outptr(void  *pData, uint  wSize);
void    OutptrOutBuff(uint  wSize);
void    Common(void  *pbData, uint  wSize);



#ifndef __PORTS
#define __PORTS

#define PUSH_ENUM(value) PushString(#value); PushString("="); PushLongAsString(value); PushChar(0x0D); PushChar(0x0A);

#endif
