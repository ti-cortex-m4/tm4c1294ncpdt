/*------------------------------------------------------------------------------
23x1024!H


------------------------------------------------------------------------------*/

#include "../include/nvram.h"



void    InitNvram(void);

bool    ReadNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
bool    PushNvramBuff(ulong  dwAddr, uint  wSize);
bool    WriteNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
bool    FreeNvramBuff(ulong  dwAddr, uint  wSize);

uchar   ReadNvramStatus(void);

bool    Test1WriteNvramBuff(ulong  dwAddr, uint  wSize);
bool    Test1ReadNvramBuff(ulong  dwAddr, uint  wSize);
bool    Test2WriteNvramBuff(ulong  dwAddr, uint  wSize, uchar  b);
bool    Test2ReadNvramBuff(ulong  dwAddr, uint  wSize, uchar  b);

uint    GetNvramStatus(void);

bool    ReadNvramBuffBare(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
bool    WriteNvramBuffBare(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
