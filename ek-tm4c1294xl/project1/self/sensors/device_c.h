/*------------------------------------------------------------------------------
DEVICE_C.H
              
 
------------------------------------------------------------------------------*/

bool    ReadResultC(void);
void    QueryOpenC(void);

void    QueryIdC(void);
bool    ReadIdC(void);

void    QueryTimeC(void);
time    ReadTimeC(void);

void    QueryControlC(void);

void    QueryVersionC(void);
void    ReadVersionC(void);

void    QueryEnergyAbsC(void);
void    QueryEnergyMonC(uchar  ibMonth);
void    QueryEnergyDayC(uchar  ibDay);
void    ReadEnergyC(void);

void    InitHeaderC_1(void);
void    InitHeaderC_6(void);
void    QueryHeaderC_1(void);
void    QueryHeaderC_6(void);
bool    ReadHeaderC_1(void);
bool    ReadHeaderC_6(void);

void    ReadCurrentC(void);

