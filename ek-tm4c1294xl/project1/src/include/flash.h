/*------------------------------------------------------------------------------
FLASH.H

 Ќастройки флэш-пам€ти
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH


// размер страницы
#define wPAGE_SIZE      528

// размер страницы, доступный дл€ записи данных пользовател€
#define wFREEPAGE_SIZE  512

// количество страниц
#define wPAGES          8192


// количество повторов при чтении регистра состо€ни€
#define wREAD_STATUS    50000

// количество повторов при чтени€/записи страницы
#define bMAXREPEAT      8


// количество страниц на блок данных определЄнного типа
#define bUINT_CAN       (uchar)(sizeof(uint)    * bCANALS/wFREEPAGE_SIZE + 1)
#define bIMPULSE_CAN    (uchar)(sizeof(impulse) * bCANALS/wFREEPAGE_SIZE + 1)
#define bPOWER_GRP      (uchar)(sizeof(power)   * bGROUPS/wFREEPAGE_SIZE + 1)
#define bREAL_CAN       (uchar)(sizeof(real)    * bCANALS/wFREEPAGE_SIZE + 1)


// количество страниц дл€ графика профилей по получасам
#ifdef  DAYS100
#define wIMPHOUCAN_SIZE (uint)(wHOURS/4)
#else
#define wIMPHOUCAN_SIZE (uint)(wHOURS/1)
#endif


// адреса блоков данных
typedef enum
{
  DF_BEGIN              = 0,

  DF_PRIVATE            = DF_BEGIN,
  DF_GLOBAL             = DF_PRIVATE + 1,
  DF_LOGICAL            = DF_GLOBAL + 1,

  DF_GROUPS             = DF_LOGICAL + 1,

  DF_PUBLIC_TARIFFS     = DF_GROUPS + sizeof(group)*bGROUPS/wFREEPAGE_SIZE + 1,
  DF_TARIFFS_MODE       = DF_PUBLIC_TARIFFS + 1,

  DF_DAY_ZONE           = DF_TARIFFS_MODE + 1,

  DF_ZONES_POW          = DF_DAY_ZONE + 1,
  DF_ZONES_ENG          = DF_ZONES_POW + 12*bMODES,

  DF_PERIOD_POW         = DF_ZONES_ENG + 12*bMODES,
  DF_PERIOD_ENG         = DF_PERIOD_POW + 1,

  DF_RELAXS_FLAG        = DF_PERIOD_ENG + 1,
  DF_RELAXS_TARIFF      = DF_RELAXS_FLAG + 1,
  DF_RELAXS             = DF_RELAXS_TARIFF + 1,

  DF_GAPS_FLAG          = DF_RELAXS + sizeof(relaxs)/wFREEPAGE_SIZE + 1,
  DF_GAPS               = DF_GAPS_FLAG + 1,

  DF_TRANS_ENG          = DF_GAPS + sizeof(gaps)/wFREEPAGE_SIZE + 1,
  DF_TRANS_CNT          = DF_TRANS_ENG + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  DF_PULSE_HOU          = DF_TRANS_CNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  DF_PULSE_MNT          = DF_PULSE_HOU + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,

  DF_COUNT              = DF_PULSE_MNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  DF_LOSSE              = DF_COUNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  DF_LEVEL              = DF_LOSSE + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,

  DF_DIGITALS           = DF_LEVEL + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,

  DF_IMPHOUCAN          = DF_DIGITALS + sizeof(digital)*bCANALS/wFREEPAGE_SIZE + 1,
  DF_IMPDAYCAN          = DF_IMPHOUCAN + wIMPHOUCAN_SIZE,
  DF_IMPMONCAN          = DF_IMPDAYCAN + bIMPULSE_CAN*bDAYS,
  DF_POWDAYGRP          = DF_IMPMONCAN + bIMPULSE_CAN*bMONTHS,
  DF_POWMONGRP          = DF_POWDAYGRP + bPOWER_GRP*bDAYS,
  DF_CNTMONCAN          = DF_POWMONGRP + bPOWER_GRP*bMONTHS,

  DF_IMPDAYCAN_BUFF     = DF_CNTMONCAN + bREAL_CAN*bMONTHS,
  DF_IMPMONCAN_BUFF     = DF_IMPDAYCAN_BUFF + bIMPULSE_CAN,
  DF_IMPABSCAN_BUFF     = DF_IMPMONCAN_BUFF + bIMPULSE_CAN,
  DF_POWDAYGRP_BUFF     = DF_IMPABSCAN_BUFF + bIMPULSE_CAN,
  DF_POWMONGRP_BUFF     = DF_POWDAYGRP_BUFF + bPOWER_GRP,
  DF_CNTMONCAN_BUFF     = DF_POWMONGRP_BUFF + bPOWER_GRP,

  DF_PTRMNT             = DF_CNTMONCAN_BUFF + bREAL_CAN,
  DF_PTRHOU             = DF_PTRMNT + 1,
  DF_PTRDAY             = DF_PTRHOU + 1,
  DF_PTRMON             = DF_PTRDAY + 1,

  DF_END                = DF_PTRMON + 1
} flash;



#endif
