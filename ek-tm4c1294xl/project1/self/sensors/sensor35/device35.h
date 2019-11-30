/*------------------------------------------------------------------------------
DEVICE35.H


------------------------------------------------------------------------------*/

uint    GetExchange35(void);
void    IncExchange35(void);

void    PushModemAddress35(void);
void    PushSensorAddress35(void);

void    QueryTime35(void);
time    ReadTime35(void);

void    QueryControl35(time  ti);

void    QueryConfig35(void);
void    ReadConfig35(void);
uint    GetDivider35(void);

void    QueryVersion35(void);
void    ReadVersion35(void);

void    QueryEngDay35(uchar  bDay);
void    QueryEngMon35(uchar  bMonth);
void    ReadEnergy35(void);

void    ReadCurrent35(void);
