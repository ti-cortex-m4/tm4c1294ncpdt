/*------------------------------------------------------------------------------
FILES.C

 Функции чтения/записи данных по указателю
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "at45.h"



void    OpenOut(uint  wPage)
{
  wPageOut = wPage;

//  memset(&mpbPageOut, '\0', sizeof(mpbPageOut));
  wByteOut = 0;
}


bool    Save(void  *pbBase, uint  wSize)
{
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // размер свободной части буфера

    if (wSize > wFree)                          // блок данных больше размера свободной части буфера
    {                                           // заполняем всё свободное место
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite() == 0) return(0);      // записываем буфер

      OpenOut(wPageOut + 1);                    // подготавливаемся к записи следующей страницы

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO переходим на следующую позицию источника данных
      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные в буфер
      memcpy(mpbPageOut + wByteOut, pbBase, wSize);                                  
      wByteOut += wSize;                        // увеличиваем счётчик заполнения буфера

      return(1);
    }
  }
}  


bool    CloseOut()
{
  return( SafePageWrite() );
}



bool    OpenIn(uint  wPage)
{
  wPageIn = wPage;

//  memset(&mpbPageIn, '\0', sizeof(mpbPageIn));
  wByteIn = 0;

  return( SafePageRead() );
}


bool    Load(void  *pbBase, uint  wSize)
{     
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteIn;           // размер непрочитанной части буфера

    if (wSize > wFree)                          // блок данных больше размера непрочитанной части буфера
    {                                           // читаем данные из буфера
      memcpy(pbBase, mpbPageIn + wByteIn, wFree);

      if (OpenIn(wPageIn + 1) == 0) return(0);  // читаем в буфер следующую страницу

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO переходим на следующую позицию источника данных
      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные из буфера
      memcpy(pbBase, mpbPageIn + wByteIn, wSize);
      wByteIn += wSize;                         // увеличиваем счётчик заполнения буфера

      return(1);
    }
  }
}

