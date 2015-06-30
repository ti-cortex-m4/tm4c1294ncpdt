/*------------------------------------------------------------------------------
MEM_REALTIME.H


------------------------------------------------------------------------------*/

#ifndef __MEM_REALTIME
#define __MEM_REALTIME


// счётчики отработанных временных интервалов
typedef struct
{
  ulong         cdwSeconds;
  ulong         cdwMinutes1;
  ulong         cdwMinutes3;
  ulong         cdwMinutes30;
  uint          cwDays;
  uint          cwMonths;
  uint          cwYears;
} realtime1;


extern  time                    tiCurr, tiPrev;

extern  uchar                   ibSoftMnt,
                                ibSoftHou,
                                ibSoftDay, ibHardDay,
                                ibSoftMon, ibHardMon;

extern  uint                    iwHardMnt,
                                iwHardHou;

extern  uchar                   cbShowCurrentTime;



extern  realtime1               Realtime1;



extern  uchar                   bHouInc;


#endif

