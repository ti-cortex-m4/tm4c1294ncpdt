/*------------------------------------------------------------------------------
REALTIME.H


------------------------------------------------------------------------------*/

extern  bool                    fSeason;

extern  bool                    fSummer, fWinter;

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

void    ProcessTime(void);
void    Realtime(void);
