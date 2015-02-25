/*------------------------------------------------------------------------------
FILES.H

 Функции чтения/записи данных по указателю
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../include/flash.h"



void    OpenOut(uint  wPage);
boolean Save(void  *pbBase, uint  wSize, format  fo);
boolean CloseOut(format  fo);

boolean OpenIn(uint  wPage);
boolean Load(void  *pbBase, uint  wSize);

boolean SaveBuff(uint wPage, void *pbBuff, uint wSize);
boolean LoadBuff(uint wPage, void *pbBuff, uint wSize);

boolean SaveFile(file const *pfl);
boolean LoadFile(file const *pfl);
