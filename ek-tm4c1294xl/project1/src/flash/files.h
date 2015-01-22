/*------------------------------------------------------------------------------
FILES.H

 Функции чтения/записи массивов
------------------------------------------------------------------------------*/

#include        "main.h"



void    OpenOut(uint  wPage);
bit     Save(void  xdata *pbBase, uint  wSize);
bit     CloseOut();

bit     OpenIn(uint  wPage);
bit     Load(void  xdata *pbBase, uint  wSize);

