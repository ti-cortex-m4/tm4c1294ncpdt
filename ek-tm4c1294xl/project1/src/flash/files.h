/*------------------------------------------------------------------------------
FILES.H

 Функции чтения/записи данных по указателю
------------------------------------------------------------------------------*/

#include        "main.h"



void    OpenOut(uint  wPage);
bool    Save(void  *pbBase, uint  wSize);
bool    CloseOut();

bool    OpenIn(uint  wPage);
bool    Load(void  *pbBase, uint  wSize);
