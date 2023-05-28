/*------------------------------------------------------------------------------
profile_interval.h


------------------------------------------------------------------------------*/

extern  bool                    boProfileInterval;
extern  cache const             chProfileInterval;

extern  uchar                   bProfileIntervalDirect;
extern  cache const             chProfileIntervalDirect;

extern  uchar                   bProfileIntervalModem;
extern  cache const             chProfileIntervalModem;



extern  uchar                   ibProfileIntervalDig;



void    InitProfileInterval(void);
void    ResetProfileInterval(void);

uchar   GetProfileIntervalTimeout(void);
bool    IsFinishedProfileInterval(void);
