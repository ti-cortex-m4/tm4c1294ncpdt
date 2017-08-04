/*------------------------------------------------------------------------------
MEM_EXTENDED_3,C


------------------------------------------------------------------------------*/

#include "../main.h"



// флаг разрешения чтения событий
bool                    fExt3Flag;

// флаги первичного чтения событий
bool                    mpfEventStart[bCANALS];

// флаг разрешения конкретного события
bool                    mpfEventFlagA[32],
                        mpfEventFlagB[32];

// массивы событий
time                    mptiEventAB1[10],
                        mptiEventAB2[10];

// хранимые коды событий
ulong                   mpdwEventDevice[bCANALS],
                        mpdwEventPhase1[bCANALS],
                        mpdwEventPhase2[bCANALS],
                        mpdwEventPhase3[bCANALS];

// код ошибки
uchar                   bEventCode;
