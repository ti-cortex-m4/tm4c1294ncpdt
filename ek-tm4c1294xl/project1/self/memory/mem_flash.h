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

extern  uint                    cwFlashBusyCnt,
                                cwFlashBusyErr,
                                cwFlashCompareWrn,
                                cwFlashCompareErr,
                                cwFlashEraseWrn,
                                cwFlashEraseErr,
                                cwFlashReadWrn,
                                cwFlashReadErr,
                                cwFlashWriteWrn,
                                cwFlashWriteErr;

extern  uint                    cwFlashCompareErr1,
                                cwFlashCompareErr2,
                                cwFlashEraseErr1,
                                cwFlashEraseErr2,
                                cwFlashReadErr1,
                                cwFlashReadErr2,
                                cwFlashWriteErr1,
                                cwFlashWriteErr2;
