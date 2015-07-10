/*------------------------------------------------------------------------------
NVRAM.H


------------------------------------------------------------------------------*/

#ifndef __NVRAM
#define __NVRAM


#include "../label.h"
#include "../memory/mem_digitals0.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_extended_1.h"
#include "../memory/mem_extended_7.h"


// количество байтов
#define dwNVRAM_BYTES   (ulong)(128*1024)


// количество байтов служебной информации для каждой записи
#define bNVRAM_FOOTER   (uchar)(3+2+6+2)


#include "nvram_enum.txt"


#endif
