/*------------------------------------------------------------------------------
MEM_FACTORS,C


------------------------------------------------------------------------------*/

#include "../main.h"



// массив К трансформации (для энергии/мощности и значений счётчиков)
double                  mpdbTransEng[bCANALS],
                        mpdbTransCnt[bCANALS];

// массив К преобразования (для получасовых и трёхминутных интервалов)
double                  mpdbPulseHou[bCANALS],
                        mpdbPulseMnt[bCANALS];

// массив К эквивалентов
double                  mpdbValueEngHou[bCANALS],
                        mpdbValueCntHou[bCANALS],
                        mpdbValueEngMnt[bCANALS],
                        mpdbValueCntMnt[bCANALS];

// массив начальных значений счётчиков
double                  mpdbCount[bCANALS];

// массив К потерь
double                  mpdbLosse[bCANALS];

// массив отношений К преобразования
double                  mpdbLevel[bCANALS];
