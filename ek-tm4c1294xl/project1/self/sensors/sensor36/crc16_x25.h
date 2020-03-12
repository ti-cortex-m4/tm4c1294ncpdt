/*------------------------------------------------------------------------------
crc16_x25.h


------------------------------------------------------------------------------*/

void Crc16_X25(uchar  *pbData, uint  wSize);

uint    MakeCRC16_X25OutBuff(uchar  bOffset, uint  wSize);
uint    MakeCRC16_X25InBuff(uchar  bOffset, uint  wSize);
