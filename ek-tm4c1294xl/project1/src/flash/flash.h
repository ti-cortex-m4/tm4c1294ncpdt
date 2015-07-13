/*------------------------------------------------------------------------------
FLASH,H


------------------------------------------------------------------------------*/

bool    SafePageErase(uint const  wPage);
bool    SafePageRead(uint const  wPage);
bool    SafePageWrite(uint const  wPage);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
