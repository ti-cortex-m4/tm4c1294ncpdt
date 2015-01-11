/*------------------------------------------------------------------------------
PORTS.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "ports_stack.h"
#include        "ports_common.h"




extern  serial                  mpSerial[bPORTS];

extern	uchar                   ibPort;



void    Output(uint  wSize);
void    Result(uchar  bT);
void    LongResult(uchar  bT);
void    Common(void  *pbData, uint  wSize);
