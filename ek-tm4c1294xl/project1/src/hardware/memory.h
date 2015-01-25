/*------------------------------------------------------------------------------
MEMORY.H


------------------------------------------------------------------------------*/


void    InitCODE(void);

ulong   GetCODESize(void);
uint    GetCODEChecksum(void);
uint    GetBuildNumber(void);
uchar   GetBuildDate_Second(void);
uchar   GetBuildDate_Minute(void);
uchar   GetBuildDate_Hour(void);
uchar   GetBuildDate_Day(void);
uchar   GetBuildDate_Month(void);
uchar   GetBuildDate_Year(void);

void    Restart(void);
