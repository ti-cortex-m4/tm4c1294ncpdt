/*------------------------------------------------------------------------------
io_mode.h


------------------------------------------------------------------------------*/

#ifndef __IO_MODE_H__
#define __IO_MODE_H__


typedef enum
{
  IO_MODE_DEFAULT = 0,
  IO_MODE_INPUT = 1,
  IO_MODE_OUTPUT = 2
} ioMode;


#endif


void InitIOModes(void);

void InMode(uchar u);
void OutMode(uchar u);

ioMode GetIOMode(uchar u);
