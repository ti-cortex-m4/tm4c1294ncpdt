/*------------------------------------------------------------------------------
23x1024.H


------------------------------------------------------------------------------*/

void    InitNvram(void);

bool    ReadNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);
bool    WriteNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize);

uchar   ReadNvramStatus(void);
