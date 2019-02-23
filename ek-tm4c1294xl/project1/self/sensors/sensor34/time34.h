/*------------------------------------------------------------------------------
time34.h


------------------------------------------------------------------------------*/

// порог коррекции времени, секунд
#define CORRECT_LIMIT_34    10



void    SetTimeCurr34(time  tm);
time    GetTimeCurr34(void);
uchar   GetTimeCurrIndex34(void);

void    QueryTime34(void);
time    ReadTime34(void);

void    SetCorrectSecond34(int32_t dw);
void    QueryCorrect34(void);
void    ReadCorrect34(void);

void    QueryManage34(void);
void    ReadManage34(void);
