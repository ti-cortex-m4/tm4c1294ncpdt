/*------------------------------------------------------------------------------
AT45.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../settings/flash.h"



void    InitFlash(void);

bool    SafePageErase(void);
bool    SafePageRead(void);
bool    SafePageWrite(void);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
