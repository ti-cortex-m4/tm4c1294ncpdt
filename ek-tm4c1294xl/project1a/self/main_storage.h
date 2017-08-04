/*------------------------------------------------------------------------------
MAIN_STORAGE,H


------------------------------------------------------------------------------*/

#ifndef __MAIN_STORAGE
#define __MAIN_STORAGE


// сохраняемый массив памяти в FLASH
typedef struct
{
  uint          wPage;
  void         *pbBuff;
  uint          wSize;
} file;


// сохраняемый массив памяти в NVRAM
typedef struct
{
  ulong         dwAddr;
  void         *pbBuff;
  uint          wSize;
} cache;


#endif
