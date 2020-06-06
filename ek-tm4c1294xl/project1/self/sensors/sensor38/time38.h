/*------------------------------------------------------------------------------
time38.h


------------------------------------------------------------------------------*/

time    LongToTime38(ulong  dw);

void    QueryTime38(void);
time    ReadTime38(void);

void    SetCorrectSecond38(int64_t  ddw);
void    QueryCorrect38(void);
uchar   ReadCorrect38(void);

void    QueryManage38(void);
uchar   ReadManage38(void);
