/*------------------------------------------------------------------------------
MEM_REALTIME.S


------------------------------------------------------------------------------*/

#include "../main.h"



// переменные для обработки переходов времени
time                    tiCurr, tiPrev;

// индексы по кольцевым буферам
uchar                   ibSoftMnt, ibHardMnt,
                        ibSoftHou,
                        ibSoftDay, ibHardDay,
                        ibSoftMon, ibHardMon;

// индексы по кольцевому буферу
uint                    iwHardHou;

// сечетчик включения отображения текущего времени
uchar                   cbShowCurrentTime;



// счётчики отработанного времени
ulong                   cdwSeconds, cdwMinutes1, cdwMinutes3, cdwMinutes30;

// счётчики отработанного времени
uint                    cwDays, cwMonths, cwYears;



// переменная
uchar                   bHouInc;
