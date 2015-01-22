/*------------------------------------------------------------------------------
MEM_FLASH.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "settings/flash.h"



// номера читаемых/записываемых страниц и количества прочитанных/записанных байтов
uint                    wPageIn, wPageOut,
                        wByteIn, wByteOut;

// слово состояния флэш-памяти
uchar                   bStatusFlash;

// буфера читаемых/записываемых страниц флэш-памяти
uchar                   mpbPageIn[wPAGE_SIZE],
                        mpbPageOut[wPAGE_SIZE];

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
