/*------------------------------------------------------------------------------
buffer_record_39*h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_RECORD_39
#define __BUFFER_RECORD_39


typedef struct
{
  uchar         bError;
  uint64_t      ddwValue;
  time          tiValue;
  bool          fFirst;
} record39;


#endif


void    InitBuffRecord39_All(void);
void    InitBuffRecord39(void);
void    AddBuffRecord39(uint  iwStart/*, uint  cwSize*/);
record39 GetBuffRecordError(char  bError);
record39 FinishBuffRecord39(void);
