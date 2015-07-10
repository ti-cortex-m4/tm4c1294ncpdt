/*------------------------------------------------------------------------------
MEM_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"



// счетчики количества операций
ulong                   cdwNvramRead,
                        cdwNvramWrite,
                        cdwNvramFree;

// счетчики количества ошибок
uint                    cwWrnNvramRead,
                        cwErrNvramRead,
                        cwWrnNvramWrite,
                        cwErrNvramWrite,
                        cwWrnNvramFree,
                        cwErrNvramFree,
                        cwWrnNvramCompare,
                        cwErrNvramCompare;
