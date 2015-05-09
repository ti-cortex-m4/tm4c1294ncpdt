/*------------------------------------------------------------------------------
MEM_CORRECT1.C


------------------------------------------------------------------------------*/

#include "../main.h"



// массивы счётчиков величины коррекций времени
uint                    mpcwPosValueCurr[15], mpcwNegValueCurr[15],
                        mpcwPosValuePrev[15], mpcwNegValuePrev[15];

// массивы счётчиков количества коррекций времени
uint                    mpcwPosCountCurr[15], mpcwNegCountCurr[15],
                        mpcwPosCountPrev[15], mpcwNegCountPrev[15];

