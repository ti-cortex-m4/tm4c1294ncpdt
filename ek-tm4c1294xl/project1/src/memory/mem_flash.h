/*------------------------------------------------------------------------------
MEM_FLASH.H


------------------------------------------------------------------------------*/

#include "../include/flash.h"



extern  uchar                   bFlashStatus;

extern  uchar                   mpbPageIn[wPAGE_BYTES],
                                mpbPageOut[wPAGE_BYTES];

extern  uint                    cwWrnBusy,
                                cwWrnCompare,
                                cwWrnPageErase,
                                cwWrnPageRead,
                                cwWrnPageWrite,
                                cwErrCompare,
                                cwErrPageErase,
                                cwErrPageRead,
                                cwErrPageWrite;

extern  uint                    mpcwFlashControl[wPAGES_TOTAL];

extern  ulong                   cdwPageErase,
                                cdwPageRead,
                                cdwPageWrite;

extern  ulong                   cdwFlashReadBytes,
                                cdwFlashWriteBytes;
