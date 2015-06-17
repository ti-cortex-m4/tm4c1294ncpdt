/*------------------------------------------------------------------------------
NVRAM.H


------------------------------------------------------------------------------*/

#ifndef __NVRAM
#define __NVRAM


#include "../label.h"
#include "../memory/mem_digitals0.h"
#include "../memory/mem_extended_1.h"
#include "../memory/mem_extended_7.h"


// ���������� ������
#define dwNVRAM_BYTES   (ulong)(128*1024)


// ���������� ������ ��������� ���������� ��� ������ ������
#define bNVRAM_FOOTER   2


#include "nvram_enum.txt"


#endif
