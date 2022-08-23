/*------------------------------------------------------------------------------
buffer_profile_40.h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_PROFILE_40
#define __BUFFER_PROFILE_40


typedef struct
{
  bool          fExists;
  time          tmHhrEnd;
  ulong         mdwValue[4];
} profile40;


#endif



void    InitProfile40(void);
void    AddProfile40(time  tmHhrEnd, ulong  mdwValue[4]);

profile40 GetProfile40(uchar  p);
uchar   GetProfileSize40(void);
bool    IsProfileOveflow40(void);
