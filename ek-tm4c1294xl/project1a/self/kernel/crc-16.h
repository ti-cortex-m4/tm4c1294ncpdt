/*------------------------------------------------------------------------------
CRC-16!H


------------------------------------------------------------------------------*/

extern  const uchar             mpbCRCHi[0x100], mpbCRCLo[0x100];
extern  const uchar             bCRCHi, bCRCLo;

void    InitCRC(void);
void    CalcCRC(uchar  bT);
void    MakeCRC16(uchar  *pbData, uint  wSize);
