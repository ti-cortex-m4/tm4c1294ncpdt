#ifndef __MAIN_STORAGE
#define __MAIN_STORAGE


// тип 'формат данных в памяти'
typedef enum
{
  FOR_DEFAULT           = 0,
  FOR_UINT              = 1,
  FOR_REAL              = 2,
  FOR_IMPULSE           = 3,
  FOR_MAX_POWER         = 4,
} format;


// тип 'сохраняемый массив памяти"
typedef struct
{
  uint          wPage;
  void         *pbBuff;
  uint          wSize;
  format        foSelf;
} file;


#endif
