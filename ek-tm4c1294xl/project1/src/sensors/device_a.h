/*------------------------------------------------------------------------------
DEVICE_A.H
              
 Подпрограммы доступа к цифровому счётчику СЭТ-4ТМ
------------------------------------------------------------------------------*/



#ifndef SKIP_A

bit     ReadAddressA(void);
bit     ReadResultA(void);

void    QueryOpenA(void);

void    QueryIdA(void);
bit     ReadIdA(void);

void    QueryEnergyA(uchar  bTime);
void    ReadEnergyA(void);

void    QueryControlA(void);
void    QueryManageA(void);

void    QueryTimeA(void);
void    ReadTimeAltA(void);

void    QueryTopA(void);
void    ReadTopA(void);

void    QueryHeaderA(void);
void    QueryHeaderA_Plus(uchar  bSize);
void    ReadHeaderA(void);

void    QueryDataA(void);
bit     ReadDataA(void);
bit     TestDataA_Plus(uchar  ibBlock);
bit     ReadDataA_Plus(uchar  ibBlock);

void    ReadCurrentA(void);

#endif

