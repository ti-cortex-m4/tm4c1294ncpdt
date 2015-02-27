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
  wByteOut = 0;

  bBlockOut = 0;
}


void    OpenOut2(uint  wPage)
{
  wPageOut = wPage;
  wByteOut = 0;
}


boolean Save(void  *pbBase, uint  wSize, format  fo)
{
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // размер свободной части буфера

    if (wSize > wFree)                          // блок данных больше размера свободной части буфера
    {                                           // заполняем всё свободное место
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite(fo) == FALSE) return FALSE; // записываем буфер

      OpenOut2(wPageOut + 1);                   // подготавливаемся к записи следующей страницы

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO переходим на следующую позицию источника данных
      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные в буфер
      memcpy(mpbPageOut + wByteOut, pbBase, wSize);                                  
      wByteOut += wSize;                        // увеличиваем счётчик заполнения буфера

      return TRUE;
    }
  }
}  


boolean Clean(uint  wSize, format  fo)
{
uint    wFree;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // размер свободной части буфера

    if (wSize > wFree)                          // блок данных больше размера свободной части буфера
    {                                           // заполняем всё свободное место
      memset(mpbPageOut + wByteOut, 0, wFree);

      if (SafePageWrite(fo) == FALSE) return FALSE; // записываем буфер

      OpenOut2(wPageOut + 1);                   // подготавливаемся к записи следующей страницы

      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные в буфер
    	memset(mpbPageOut + wByteOut, 0, wSize);
      wByteOut += wSize;                        // увеличиваем счётчик заполнения буфера

      return TRUE;
    }
  }
}


boolean CloseOut(format  fo)
{
  return SafePageWrite(fo);
}



boolean OpenIn(uint  wPage)
{
  wPageIn = wPage;
  wByteIn = 0;

  return( SafePageRead() );
}


boolean Load(void  *pbBase, uint  wSize)
{     
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteIn;           // размер непрочитанной части буфера

    if (wSize > wFree)                          // блок данных больше размера непрочитанной части буфера
    {                                           // читаем данные из буфера
      memcpy(pbBase, mpbPageIn + wByteIn, wFree);

      if (OpenIn(wPageIn + 1) == 0) return FALSE;  // читаем в буфер следующую страницу

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO переходим на следующую позицию источника данных
      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные из буфера
      memcpy(pbBase, mpbPageIn + wByteIn, wSize);
      wByteIn += wSize;                         // увеличиваем счётчик заполнения буфера

      return TRUE;
    }
  }
}



boolean SaveBuff(uint wPage, void *pbBuff, uint wSize, format  fo)
{
  OpenOut(wPage);

  if (Save(pbBuff, wSize, fo) == FALSE)
    return FALSE;

  return CloseOut(fo);
}


boolean LoadBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenIn(wPage);
  return Load(pbBuff, wSize);
}



boolean SaveFile(file const *pfl)
{
  return SaveBuff(pfl->wPage, pfl->pbBuff, pfl->wSize, pfl->foSelf);
}


boolean LoadFile(file const *pfl)
{
  return LoadBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}
