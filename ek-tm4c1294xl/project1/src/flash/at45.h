/*------------------------------------------------------------------------------
AT45.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../settings/flash.h"



void    InitFlash(void);

bit     SafePageErase(void);
bit     SafePageRead(void);
bit     SafePageWrite(void);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
