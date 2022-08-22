/*------------------------------------------------------------------------------
buffer_array_40.h


------------------------------------------------------------------------------*/

void    MonitorArray40(void);

void    InitPush40(void);
void    PushChar40(uchar  b);
bool    IsPushOverflow40(void);

void    InitPop40(void);
uint    GetPopCapacity40(void);
uchar   PopChar40(void);
uint    PopInt40(void);
ulong   PopLong40(void);
uint64_t PopLongLong40(void);
time    PopTimeDate40(void);
