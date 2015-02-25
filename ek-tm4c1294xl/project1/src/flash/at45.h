/*------------------------------------------------------------------------------
AT45.H

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include        "../include/flash.h"



void    InitFlash(void);

boolean SafePageErase(void);
boolean SafePageRead(void);
boolean SafePageWrite(format  fo);

uint    GetFlashStatus(void);
boolean GetFlashChecksum(void);
