/*------------------------------------------------------------------------------
MEM_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"



// счетчики количества операций
ulong                   cdwNvramReadBuff,
                        cdwNvramWriteBuff,
                        cdwNvramFreeBuff;

// счетчики количества байтов
ulong                   cdwNvramReadByte,
                        cdwNvramWriteByte;

// счетчики количества ошибок
uint                    cwNvramReadWrn,
                        cwNvramReadErr,
                        cwNvramWriteWrn,
                        cwNvramWriteErr,
                        cwNvramFreeWrn,
                        cwNvramFreeErr,
                        cwNvramCompareWrn,
                        cwNvramCompareErr;
