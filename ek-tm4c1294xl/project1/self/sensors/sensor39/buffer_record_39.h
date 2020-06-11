/*------------------------------------------------------------------------------
buffer_record_39*h


------------------------------------------------------------------------------*/

#ifndef __buffer_record_39
#define __buffer_record_39


typedef struct
{
  uchar         bError;
  uint64_t      ddwValue;
  time          tiValue;
  bool          fFirst;
} buff_y;


#endif



void    StartBufferY(void);
void    AddBufferY(uint  iwStart, uint  cwSize);
buff_y  FinishBufferY(void);
