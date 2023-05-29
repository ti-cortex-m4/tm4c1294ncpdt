/*------------------------------------------------------------------------------
profile_interval.h


------------------------------------------------------------------------------*/

extern  bool                    boProfileInterval;
extern  cache const             chProfileInterval;

extern  uchar                   bProfileIntervalDirect;
extern  cache const             chProfileIntervalDirect;

extern  uchar                   bProfileIntervalModem;
extern  cache const             chProfileIntervalModem;



void    InitProfileInterval(void);
void    ResetProfileInterval(void);

uchar   GetProfileIntervalTimeout(void);
bool    IsFinishedProfileInterval(void);

uchar   GetProfileIntervalDig(void);
uchar   GetAndResetProfileIntervalDig(void);
void    SetProfileIntervalDig(uchar  c);

void    ShowProfileIntervalInitMesage(void);
void    ShowProfileIntervalBeforeMesage(void);
void    ShowProfileIntervalAfterMesage(void);
