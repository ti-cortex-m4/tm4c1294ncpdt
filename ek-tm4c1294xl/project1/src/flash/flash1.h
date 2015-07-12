/*------------------------------------------------------------------------------
FLASH1.H


------------------------------------------------------------------------------*/

void    InitFlash1(void);

bool    SafePageErase(void);
bool    SafePageRead(void);
bool    SafePageWrite(void);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
