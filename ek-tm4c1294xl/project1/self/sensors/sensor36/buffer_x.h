/*------------------------------------------------------------------------------
buffers_x.h


------------------------------------------------------------------------------*/

void    InitPushX(void);
void    PushCharX(uchar  b);

void    InitPopX(void);
uchar   PopCharX(void);
uint    PopIntBigX(void);
ulong   PopLongBigX(void);
time    PopTimeDateX(void);
uint64_t PopULong64X(void);
