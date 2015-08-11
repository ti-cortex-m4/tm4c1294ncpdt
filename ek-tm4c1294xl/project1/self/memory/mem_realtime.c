/*------------------------------------------------------------------------------
MEM_REALTIME.S


------------------------------------------------------------------------------*/

#include "../main.h"
#include "mem_realtime.h"



// переменные для обработки переходов времени
time                    tiCurr, tiPrev;

// индексы по кольцевым буферам
uchar                   ibSoftMnt,
                        ibSoftHou,
                        ibSoftDay, ibHardDay,
                        ibSoftMon, ibHardMon;

// индексы по кольцевому буферу
uint                    iwHardMnt,
                        iwHardHou;

// сечетчик включения отображения текущего времени
uchar                   cbShowCurrentTime;



// счётчики отработанных временных интервалов
realtime1               Realtime1;



// переменная
uchar                   bHouInc;
