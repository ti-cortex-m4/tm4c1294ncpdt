/*------------------------------------------------------------------------------
DEVICE_B!H


------------------------------------------------------------------------------*/

#ifndef SKIP_B

// ������� ����� ��������� �������, ������
#define bMAJORCORRECT_B 230

// ������� ����� ��������� �������, ������
#define wLIMITCORRECT_B 1800

//
#define bBLOCKS_B       20



extern  uchar                   bVersionB1, bVersionB2, bVersionB3;



//bit     ReadAddressB(void);
bool    ReadResultB(void);

void    QueryOpenB(void);

void    QuerySerialB(void);
ulong   ReadSerialB(void);

void    QueryVersionB(void);
void    ReadVersionB(void);
bool    TestVersionB710(void);
bool    TestVersionB910(void);

void    QueryIdB(void);
bool    ReadIdB(void);

void    QueryEnergyB(uchar  bTime);
void    ReadEnergyB(void);

void    QueryControlB(void);
//void    QueryManageB(void);

void    QueryTimeB(void);
time    ReadTimeB(void);

void    ReadCurrentB(void);

#endif
