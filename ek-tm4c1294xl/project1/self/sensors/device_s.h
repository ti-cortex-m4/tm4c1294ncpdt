/*------------------------------------------------------------------------------
DEVICE_S.C


------------------------------------------------------------------------------*/

void    PushAddressS(void);

void    QueryTimeS(void);
time    ReadTimeS(void);

void    QueryControlS(time  ti);

void    QueryConfigS(void);
void    ReadConfigS(void);

void    QueryVersionS(void);
void    ReadVersionS(void);

void    QueryEngDayS(uchar  bDay);
void    QueryEngMonS(uchar  bMonth);
void    ReadEnergyS(void);

void    InitHeaderS(void);
void    QueryHeaderS(void);
bool    ReadHeaderS(void);

void    ReadCurrentS(void);
