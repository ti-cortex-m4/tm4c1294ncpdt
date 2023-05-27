/*------------------------------------------------------------------------------
profile_interval.h


------------------------------------------------------------------------------*/

extern  bool                    boProfileInterval;
extern  cache const             chProfileInterval;
extern  uchar                   ibProfileIntervalDig;



void    InitProfileInterval(void);
void    ResetProfileInterval(void);

uchar   GetProfileIntervalTimeout(void);
bool    IsStopProfileInterval(void);
