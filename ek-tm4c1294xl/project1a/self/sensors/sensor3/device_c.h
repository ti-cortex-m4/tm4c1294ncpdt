/*------------------------------------------------------------------------------
DEVICE_C!H


------------------------------------------------------------------------------*/

bool    ReadResultC(void);
void    QueryOpenC(void);

void    QuerySerialC(void);
ulong   ReadSerialC(void);

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

void    ReadCurrentC(void);

