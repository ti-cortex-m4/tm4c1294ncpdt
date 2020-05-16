/*------------------------------------------------------------------------------
buffer_y.h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_Y
#define __BUFFER_Y


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
