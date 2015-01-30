/*------------------------------------------------------------------------------
PORTS.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "ports_stack.h"
#include        "ports_common.h"
#include        "include/queries.h"
#include        "include/queries2.h"



extern  serial                  mpSerial[bPORTS];

extern	uchar                   ibPort;



void    Output(uint  wSize);
void    Result(uchar  bT);
void    LongResult(uchar  bT);
void    Outptr(void  *pData, uint  wSize);
void    OutptrOutBuff(uint  wSize);
void    Common(void  *pbData, uint  wSize);
