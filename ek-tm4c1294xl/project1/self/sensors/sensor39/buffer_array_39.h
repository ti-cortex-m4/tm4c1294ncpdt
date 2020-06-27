/*------------------------------------------------------------------------------
buffer_array_39.h


------------------------------------------------------------------------------*/

void    MonitorArray39(void);

void    InitPush39(void);
void    PushChar39(uchar  b);
bool    IsPushOverflow(void);

void    InitPop39(void);
uint    GetPopCapacity39(void);
uchar   PopChar39(void);
uint    PopInt39(void);
ulong   PopLong39(void);
uint64_t PopLongLong39(void);
time    PopTimeDate39(void);
