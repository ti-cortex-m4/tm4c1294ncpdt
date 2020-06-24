/*------------------------------------------------------------------------------
NVRAM!H


------------------------------------------------------------------------------*/

#ifndef __NVRAM
#define __NVRAM


#include "../label_global.h"
#include "../kernel/asserts.h"
#include "../realtime/period30.h"
#include "../serial/auto_flow.h"
#include "../digitals/serials.h"
#include "../digitals/review/review.h"
#include "../memory/mem_groups.h"
#include "../memory/mem_digitals0.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_phones.h"
#include "../memory/mem_phones2.h"
#include "../memory/mem_params0.h"
#include "../memory/mem_params.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_schedule.h"
#include "../memory/mem_limits.h"
#include "../memory/mem_uni.h"
#include "../memory/mem_current.h"
#include "../memory/mem_extended_1.h"
#include "../memory/mem_extended_3.h"
#include "../memory/mem_extended_7.h"
#include "../memory/mem_records.h"
#include "../memory/mem_gps.h"
#include "../memory/mem_correct1.h"
#include "../memory/mem_correct2.h"
#include "../memory/mem_correct3.h"
#include "../digitals/address/address2.h"


// количество байтов
#define dwNVRAM_BYTES   (ulong)(128*1024)


// количество байтов служебной информации для каждой записи
#define bNVRAM_PREFIX   (uchar)(3+2)
#define bNVRAM_SUFFIX   (uchar)(6+2)
#define bNVRAM_MARGIN   (uchar)(3+2+6+2)


#include "../generated/nvram_enum.txt"


#endif
