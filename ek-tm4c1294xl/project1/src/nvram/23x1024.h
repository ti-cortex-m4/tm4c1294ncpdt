/*------------------------------------------------------------------------------
23x1024.H


------------------------------------------------------------------------------*/

#include "../include/nvram.h"



void    InitNvram(void);

bool    ReadNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
bool    PushNvramBuff(ulong  dwAddr, uint  wSize);
bool    WriteNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
bool    FreeNvramBuff(ulong  dwAddr, uint  wSize);

uchar   ReadNvramStatus(void);
