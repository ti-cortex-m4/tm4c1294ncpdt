/*------------------------------------------------------------------------------
crc16.h


------------------------------------------------------------------------------*/

extern uchar bCRCHi, bCRCLo;



void InitCRC16(void);
void CalcCRC16(uchar b);
void MakeCRC16(uchar *pbData, uint wSize);
