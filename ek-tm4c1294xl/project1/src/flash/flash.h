/*------------------------------------------------------------------------------
FLASH.H


------------------------------------------------------------------------------*/

bool    SafePageErase(void);
bool    SafePageRead(void);
bool    SafePageWrite(void);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
