/*------------------------------------------------------------------------------
buffers_x.h


------------------------------------------------------------------------------*/

void    MonitorX(void);

void    InitPushX(void);
void    PushCharX(uchar  b);

void    InitPopX(void);
uint    GetPopCapacity(void);
uchar   PopCharX(void);
uint    PopIntBigX(void);
ulong   PopLongBigX(void);
uint64_t PopLong64X(void);
time    PopTimeDateX(void);
