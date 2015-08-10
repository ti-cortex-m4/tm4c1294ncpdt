/*------------------------------------------------------------------------------
MEM_FLASH.H


------------------------------------------------------------------------------*/

#include "../include/flash.h"



extern  uchar                   bFlashStatus;

extern  uchar                   mpbPageIn[wPAGE_BYTES],
                                mpbPageOut[wPAGE_BYTES];

extern  uint                    mpcwFlashControl[wPAGES_TOTAL];

extern  ulong                   cdwFlashErasePage,
                                cdwFlashReadPage,
                                cdwFlashWritePage;

extern  ulong                   cdwFlashReadByte,
                                cdwFlashWriteByte;

extern  uint                    cwFlashBusyWrn,
                                cwFlashCompareWrn,
                                cwFlashEraseWrn,
                                cwFlashReadWrn,
                                cwFlashWriteWrn,
                                cwFlashCompareErr,
                                cwFlashEraseErr,
                                cwFlashReadErr,
                                cwFlashWriteErr;
