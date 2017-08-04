/*------------------------------------------------------------------------------
FLASH,H


------------------------------------------------------------------------------*/

bool    SafePageErase(uint const  wPageOut);
bool    SafePageRead(uint const  wPageIn);
bool    SafePageWrite(uint const  wPageOut);

uint    GetFlashStatus(void);
uint    GetFlashStatus1(void);
uint    GetFlashStatus2(void);

bool    GetFlashChecksum(void);
