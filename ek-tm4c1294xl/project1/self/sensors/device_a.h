/*------------------------------------------------------------------------------
DEVICE_A!H


------------------------------------------------------------------------------*/

#ifndef SKIP_A

// верхний порог коррекции времени, секунд
#define bMAJORCORRECT_A 110

// верхний порог коррекции времени, секунд
#define wLIMITCORRECT_A 1800

//
#define bBLOCKS_A       10



bool    ReadAddressA(void);
bool    ReadResultA(void);

void    QueryOpenA(void);

void    QueryIdA(void);
bool    ReadIdA(void);

void    QueryEnergyA(uchar  bTime);
void    ReadEnergyA(void);

void    QueryControlA(void);
void    QueryManageA(void);

void    QueryTimeA(void);
time    ReadTimeA(void);

void    QueryTopA(void);
void    ReadTopA(void);

void    QueryHeaderA(void);
void    QueryHeaderA_Plus(uchar  bSize);
void    ReadHeaderA(void);

void    QueryDataA(void);
bool    ReadDataA(void);
bool    TestDataA_Plus(uchar  ibBlock);
bool    ReadDataA_Plus(uchar  ibBlock);

void    ReadCurrentA(void);

#endif
