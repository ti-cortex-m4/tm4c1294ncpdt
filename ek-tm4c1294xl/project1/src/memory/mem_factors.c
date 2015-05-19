/*------------------------------------------------------------------------------
MEM_FACTORS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// массив К трансформации (для энергии/мощности и показаний счётчиков)
real                    mpreTransEng[bCANALS],
                        mpreTransCnt[bCANALS];

// массив К преобразования (для получасовых и трёхминутных интервалов)
real                    mprePulseHou[bCANALS],
                        mprePulseMnt[bCANALS];

// массив К эквивалентов
real                    mpreValueEngHou[bCANALS],
                        mpreValueCntHou[bCANALS],
                        mpreValueEngMnt[bCANALS],
                        mpreValueCntMnt[bCANALS];

// массив показаний счётчиков
real                    mpreCount[bCANALS];

// массив К потерь
real                    mpreLosse[bCANALS];

// массив отношений К преобразования
real                    mpreLevel[bCANALS];
