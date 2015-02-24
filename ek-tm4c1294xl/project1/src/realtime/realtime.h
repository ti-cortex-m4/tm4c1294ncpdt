/*------------------------------------------------------------------------------
REALTIME.H


------------------------------------------------------------------------------*/

extern  bool                    fActive;


uchar   GetCurrHouIndex(void);
uint    GetDayHouIndex(uchar  bDay);

uchar   PrevSoftMnt(void);
uchar   PrevSoftHou(void);
uint    PrevHardHou(void);
uchar   PrevSoftDay(void);
uchar   PrevHardDay(void);
uchar   PrevSoftMon(void);
uchar   PrevHardMon(void);

void    InitRealtime(void);
void    StartRealtime(void);

void    Realtime(void);
