/*------------------------------------------------------------------------------
REALTIME!H


------------------------------------------------------------------------------*/

#include "../memory/mem_realtime.h"



extern  bool                    fSeason;

extern  bool                    fSummer, fWinter;

extern  bool                    fActive;

extern  bool                    fCurrent, fProfile;



uchar   GetCurrHouIndex(void);
uint    GetDayHhrIndex(uchar  ibDay);

uchar   PrevSoftMnt(void);
uint    PrevHardMnt(void);
uchar   PrevSoftHou(void);
uint    PrevHardHou(void);
uchar   PrevSoftDay(void);
uchar   PrevHardDay(void);
uchar   PrevSoftMon(void);
uchar   PrevHardMon(void);
uchar   PrevSoftTim(void);

void    ProcessTime(void);
void    RunRealtime(void);
