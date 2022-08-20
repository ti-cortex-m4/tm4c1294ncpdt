/*------------------------------------------------------------------------------
profile40.h


------------------------------------------------------------------------------*/

void    SetTime_Profile40(time  tm);
time    GetTime_Profile40(void);
void    SetScaler_Profile40(double  db);

void    InitHeader40(void);
t2time  QueryHeader40(void);
bool    ReadHeader40(void);

double2 TestProfile40(void);
