/*------------------------------------------------------------------------------
AT45.H

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include        "../include/flash.h"



void    InitFlash(void);

bool    SafePageErase(void);
bool    SafePageRead(void);
bool    SafePageWrite(void);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
