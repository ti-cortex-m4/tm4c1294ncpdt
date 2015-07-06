/*------------------------------------------------------------------------------
PRINT2,H


------------------------------------------------------------------------------*/

#define ENABLE_PRINT2



void    x_init(void);
void    x_done(void);

void    x_str(char const  *psz);
void    x_bytedec(uchar  b);
void    x_bytehex(uchar  b);
void    x_intdec(uint  w);
void    x_longdec(ulong  dw);
void    x_time(time  ti);
