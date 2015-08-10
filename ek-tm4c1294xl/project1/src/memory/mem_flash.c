/*------------------------------------------------------------------------------
MEM_FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



// слово состояния флэш-памяти
uchar                   bFlashStatus;

// буфера читаемых/записываемых страниц флэш-памяти
uchar                   mpbPageIn[wPAGE_BYTES],
                        mpbPageOut[wPAGE_BYTES];

// счётчики для контроля состояния флэш-памяти
uint                    cwWrnBusy,
                        cwWrnCompare,
                        cwWrnPageErase,
                        cwWrnPageRead,
                        cwWrnPageWrite,
                        cwErrCompare,
                        cwErrPageErase,
                        cwErrPageRead,
                        cwErrPageWrite;

// счетчик количества записей страниц флэш-памяти
uint                    mpcwFlashControl[wPAGES_TOTAL];

// счётчики количества операций
ulong                   cdwPageErase,
                        cdwPageRead,
                        cdwPageWrite;

// счетчики количества байтов
ulong                   cdwFlashReadBytes,
                        cdwFlashWriteBytes;
