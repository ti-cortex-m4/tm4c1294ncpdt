/*------------------------------------------------------------------------------
CRC-16.H


------------------------------------------------------------------------------*/

extern  uchar                   mpbCRCHi[0x100], mpbCRCLo[0x100];
extern  uchar                   bCRCHi,bCRCLo;

void    MakeCRC16(uchar  *pbData, uint  wSize);
