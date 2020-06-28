/*------------------------------------------------------------------------------
buffer_record_39.h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_RECORD_39
#define __BUFFER_RECORD_39


typedef struct
{
  uchar         bError;
  uint64_t      ddwValue;
  time          tmValue;
  bool          fFirst;
} record39;


#endif


void    InitRecord39_FragmentProfile39(void);
void    InitRecord39(void);
void    AddRecord39(uint  iwStart);
record39 GetRecordError39(char  bError);
record39 FinishRecord39(void);
