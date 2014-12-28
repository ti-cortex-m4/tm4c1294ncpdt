/*------------------------------------------------------------------------------
MESSAGES.H


------------------------------------------------------------------------------*/

#include        "main.h"



extern  char const              szClear[],
                                szAlarm[],
                                szWarning[],
                                szWaiting[],
                                szZones[],
                                szTariffs[],
                                szEnergy[],
                                szPower[],
                                szCounters[],
                                szCountersB[],
                                szImpulseA[],
                                szImpulseB[],
                                szOnCanals[],
                                szOnGroups[],
                                szForPower[],
                                szForEnergy[],
                                szForDigital[],
                                szOn12Months[],
                                szOnMinute[],
                                szOnHour[],
                                szOnDay[],
                                szOnMonth[],
                                szMiddle[],
                                szCurrMnt[],
                                szCurrHou[],
                                szPrevHou[],
                                szDayCurr[],
                                szDayPrev[],
                                szMonCurr[],
                                szMonPrev[],
                                szAbsolute[],
                                szMaximum[],
                                szFull[],
                                szMorning[],
                                szEvening[],
                                szTops[],
                                szMid[],
                                szBottom[],
                                szBadFlash[],
                                szBadCODE[],
                                szBadXDATA[],
                                szBadRTC1[],
                                szBadRTC2[],
                                szError[],
                                szDirectEscU[],
                                szDirectEscV[],
                                szDirectEscS[],
                                szDirectParam[],
                                szGraphic[],
                                szBlocking[],
                                szEmpty[],
                                szYes[],
                                szNo[];



void    Work(void);
void    Setting(void);
void    Clear(void);
void    Error(void);
void    OK(void);
void    Stop(void);
void    Waiting(void);
void    Canal(void);
void    Group(void);
void    Param(void);
void    Number(void);
void    Port(void);
void    Address(void);
void    Hour(void);
void    Day(void);
void    Month(void);
void    Quarter(void);
