/*------------------------------------------------------------------------------
time38.h


------------------------------------------------------------------------------*/

time    SecondsToTime38(ulong  dw);
ulong   TimeToSeconds38(time  ti);

void    QueryTime38(void);
time    ReadTime38(void);

void    SetCorrectSecond38(int64_t  ddw);
void    QueryCorrect38(void);
uchar   ReadCorrect38(void);

void    QueryManage38(void);
uchar   ReadManage38(void);
