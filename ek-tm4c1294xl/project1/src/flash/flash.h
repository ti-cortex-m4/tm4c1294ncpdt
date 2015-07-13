/*------------------------------------------------------------------------------
FLASH,H


------------------------------------------------------------------------------*/

bool    SafePageErase(uint const  wPageOut);
bool    SafePageRead(uint const  wPageIn);
bool    SafePageWrite(uint const  wPageOut);

uint    GetFlashStatus(void);
bool    GetFlashChecksum(void);
