/*------------------------------------------------------------------------------
PROFILE_CORE!H


------------------------------------------------------------------------------*/

extern  cache const             chEnblCurrent;
extern  cache const             chEnblProfile;

extern  cache const             chTimeoutCurrent;
extern  cache const             chTimeoutProfile;

extern  bool                    boProfileInterval;
extern  cache const             chProfileInterval;
extern  uchar                   ibProfileIntervalDig;



void    InitProfile(void);
void    ResetProfile(void);
