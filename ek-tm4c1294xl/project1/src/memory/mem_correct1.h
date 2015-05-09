/*------------------------------------------------------------------------------
MEM_CORRECT1,H


------------------------------------------------------------------------------*/

// величины дл€ коррекций времени вперед и назад, за текущий и предыдущий мес€цы, по каждому из видов коррекции
typedef struct
{
// массивы величин коррекций времени
uint            mpwPosValueCurr[15],
                mpwNegValueCurr[15],
                mpwPosValuePrev[15],
                mpwNegValuePrev[15];

// массивы количеств коррекций времени
uint            mpwPosCountCurr[15],
                mpwNegCountCurr[15],
                mpwPosCountPrev[15],
                mpwNegCountPrev[15];
} correct1;



extern  correct1                Correct1;
