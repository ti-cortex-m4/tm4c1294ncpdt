/*------------------------------------------------------------------------------
profile38.h


------------------------------------------------------------------------------*/

#ifndef __PROFILE38
#define __PROFILE38


typedef struct
{
  time          tiTime;
  uchar         bStatus;
  ulong         mpdwValue[4];
} profile38;


#endif



extern  time                    tiValue38;
extern  ulong                   dwValue38;

extern  uint                    cwShutdown38;



void    InitHeader38(void);
void    QueryHeader38(void);
uchar   PushIndex38(uint  iw30MinRel);
void    QueryProfile38(uint  iw30MinRelStart, uint  iw30MinRelEnd);
bool    ReadData38(void);

void    RunProfile38(void);
