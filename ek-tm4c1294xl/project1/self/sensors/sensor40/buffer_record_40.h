/*------------------------------------------------------------------------------
buffer_record_39.h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_RECORD_40
#define __BUFFER_RECORD_40


typedef struct
{
  uchar         bError;
  ulong         mdwValue[4];
  time          tmValue;
  bool          fFirst;
} record40;


#endif


void    InitRecord40(void);
void    AddRecord40(uint  iwStart);

bool    FinishRecord40_AddProfiles40(void);
bool    FinishRecord40_Monitor(void);
