/*------------------------------------------------------------------------------
FILES.C

 Функции чтения/записи данных по указателю
------------------------------------------------------------------------------*/

#include        <string.h>
#include "../main.h"
#include "../memory/mem_flash.h"
#include "flash.h"
#include "files.h"



uint    wPageOut_, wPageIn_;



void    OpenOut(uint  wPage)
{
  wPageOut_ = wPage;
  wByteOut = 0;
}


void ClearOut(void)
{
  memset(&mpbPageOut, 0, sizeof(mpbPageOut));
}


bool Save(void  *pbBase, uint  wSize)
{
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wLEAF_BYTES - wByteOut;          // размер свободной части буфера

    if (wSize > wFree)                          // блок данных больше размера свободной части буфера
    {                                           // заполняем всё свободное место
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite(wPageOut_) == false) return false; // записываем буфер

      OpenOut(wPageOut_ + 1);                    // подготавливаемся к записи следующей страницы

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO переходим на следующую позицию источника данных
      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные в буфер
      memcpy(mpbPageOut + wByteOut, pbBase, wSize);                                  
      wByteOut += wSize;                        // увеличиваем счётчик заполнения буфера

      return true;
    }
  }

  return true;
}  

/*
bool Clean(uint  wSize)
{
uint    wFree;

  while (wSize > 0)
  {
    wFree = wLEAF_BYTES - wByteOut;          // размер свободной части буфера

    if (wSize > wFree)                          // блок данных больше размера свободной части буфера
    {                                           // заполняем всё свободное место
      memset(mpbPageOut + wByteOut, 0, wFree);

      if (SafePageWrite() == false) return false; // записываем буфер

      OpenOut(wPageOut + 1);                    // подготавливаемся к записи следующей страницы

      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные в буфер
    	memset(mpbPageOut + wByteOut, 0, wSize);
      wByteOut += wSize;                        // увеличиваем счётчик заполнения буфера

      return true;
    }
  }
}
*/

bool CloseOut(void)
{
  return SafePageWrite(wPageOut_);
}



bool    OpenIn(uint  wPage)
{
  wPageIn_ = wPage;
  wByteIn = 0;

  return( SafePageRead(wPageIn_) );
}


void ClearIn(void)
{
  memset(&mpbPageIn, 0, sizeof(mpbPageIn));
}


bool Load(void  *pbBase, uint  wSize)
{     
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wLEAF_BYTES - wByteIn;           // размер непрочитанной части буфера

    if (wSize > wFree)                          // блок данных больше размера непрочитанной части буфера
    {                                           // читаем данные из буфера
      memcpy(pbBase, mpbPageIn + wByteIn, wFree);

      if (OpenIn(wPageIn_ + 1) == 0) return false;  // читаем в буфер следующую страницу

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO переходим на следующую позицию источника данных
      wSize  -= wFree;                          // уменьшаем размер блока данных
    }
    else
    {                                           // заносим все данные из буфера
      memcpy(pbBase, mpbPageIn + wByteIn, wSize);
      wByteIn += wSize;                         // увеличиваем счётчик заполнения буфера

      return true;
    }
  }

  return true;
}



bool SaveBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenOut(wPage);

  if (Save(pbBuff, wSize) == false)
    return false;

  return CloseOut();
}

/*
bool CleanBuff(uint wPage, uint wSize)
{
  OpenOut(wPage);

  if (Clean(wSize) == false)
    return false;

  return CloseOut();
}
*/

bool LoadBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenIn(wPage);
  return Load(pbBuff, wSize);
}



bool SaveFile(file const *pfl)
{
  return SaveBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}


bool LoadFile(file const *pfl)
{
  return LoadBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}


// TODO читать побайтно и хранить счетчик записей
