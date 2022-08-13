/*------------------------------------------------------------------------------
buffer_record_39.h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_RECORD_39
#define __BUFFER_RECORD_39


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
record39 GetRecordError39(char  bError);
bool    FinishRecord39(void);
bool    FinishRecordProfile39(void);
