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
} record39;


#endif


void    InitRecord39(void);
void    AddRecord39(uint  iwStart);
bool    FinishRecord39(void);
bool    FinishRecordProfile39(void);
