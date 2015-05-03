/*------------------------------------------------------------------------------
FILES.H

 Функции чтения/записи данных по указателю
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



void    OpenOut(uint  wPage);
void    ClearOut(void);
boolean Save(void  *pbBase, uint  wSize);
boolean Clean(uint  wSize);
boolean CloseOut(void);

boolean OpenIn(uint  wPage);
void    ClearIn(void);
boolean Load(void  *pbBase, uint  wSize);

boolean SaveBuff(uint wPage, void *pbBuff, uint wSize);
boolean CleanBuff(uint wPage, uint wSize);
boolean LoadBuff(uint wPage, void *pbBuff, uint wSize);

boolean SaveFile(file const *pfl);
boolean LoadFile(file const *pfl);
