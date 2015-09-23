/*------------------------------------------------------------------------------
MEM_FLASH!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



// слово состояния флэш-памяти
uchar                   bFlashStatus;

// буфера читаемых/записываемых страниц флэш-памяти
uchar                   mpbPageIn[wPAGE_BYTES],
                        mpbPageOut[wPAGE_BYTES];

// счетчик количества записей страниц флэш-памяти
uint                    mpcwFlashControl[wPAGES_TOTAL];

// счётчики количества операций
ulong                   cdwFlashErasePage,
                        cdwFlashReadPage,
                        cdwFlashWritePage;

// счетчики количества байтов
ulong                   cdwFlashReadByte,
                        cdwFlashWriteByte;

// счетчики количества ошибок
uint                    cwFlashBusyCnt,
                        cwFlashBusyErr,
                        cwFlashCompareWrn,
                        cwFlashCompareErr,
                        cwFlashEraseWrn,
                        cwFlashEraseErr,
                        cwFlashReadWrn,
                        cwFlashReadErr,
                        cwFlashWriteWrn,
                        cwFlashWriteErr;

// счетчики количества ошибок
uint                    cwFlashCompareErr1,
                        cwFlashCompareErr2,
                        cwFlashEraseErr1,
                        cwFlashEraseErr2,
                        cwFlashReadErr1,
                        cwFlashReadErr2,
                        cwFlashWriteErr1,
                        cwFlashWriteErr2;
