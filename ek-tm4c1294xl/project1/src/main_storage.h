/*------------------------------------------------------------------------------
MAIN_STORAGE.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_STORAGE
#define __MAIN_STORAGE


// тип 'сохраняемый массив памяти"
typedef struct
{
  uint          wPage;
  void         *pbBuff;
  uint          wSize;
} file;


#endif
