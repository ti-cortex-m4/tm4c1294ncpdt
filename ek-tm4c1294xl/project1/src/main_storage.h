/*------------------------------------------------------------------------------
MAIN_STORAGE.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_STORAGE
#define __MAIN_STORAGE


// ��� '����������� ������ ������"
typedef struct
{
  uint          wPage;
  void         *pbBuff;
  uint          wSize;
} file;


// ��� '����������� ������ ������"
typedef struct
{
  ulong         dwAddr;
  void         *pbBuff;
  uint          wSize;
} cache;


#endif
