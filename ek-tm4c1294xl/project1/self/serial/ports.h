/*------------------------------------------------------------------------------
PORTS!H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/states.h"
#include "../include/queries.h"
#include "../include/queries255.h"
#include "../memory/mem_ports.h"
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

#define PUSH_VALUE(value) PushString(#value); PushString("#"); PushLongAsString(value); PushChar(0x0D); PushChar(0x0A);
#define PUSH_ADDRESS(value) PushString(#value); PushString("="); PushLongAsString(value); PushChar(0x0D); PushChar(0x0A);

#endif
