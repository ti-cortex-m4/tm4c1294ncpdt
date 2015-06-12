/*------------------------------------------------------------------------------
23x1024.H


------------------------------------------------------------------------------*/

void    InitNvram(void);

void    ReadNvramBuff(uchar  *pbBuff, ulong  dwAddr, uint  wSize);
bool    WriteNvramBuff(uchar  *pbBuff, ulong  dwAddr, uint  wSize);

uchar   ReadNvramStatus(void);
