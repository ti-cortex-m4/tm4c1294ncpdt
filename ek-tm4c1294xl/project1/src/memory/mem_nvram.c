/*------------------------------------------------------------------------------
MEM_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"



// счетчики количества операций
ulong                   cdwNvramReadBuffs,
                        cdwNvramWriteBuffs,
                        cdwNvramFreeBuffs;

// счетчики количества байтов
ulong                   cdwNvramReadBytes,
                        cdwNvramWriteBytes;

// счетчики количества ошибок
uint                    cwWrnNvramRead,
                        cwErrNvramRead,
                        cwWrnNvramWrite,
                        cwErrNvramWrite,
                        cwWrnNvramFree,
                        cwErrNvramFree,
                        cwWrnNvramCompare,
                        cwErrNvramCompare;
