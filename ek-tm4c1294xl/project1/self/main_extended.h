/*------------------------------------------------------------------------------
MAIN_EXTENDED,H


------------------------------------------------------------------------------*/

#ifndef __MAIN_EXTENDED
#define __MAIN_EXTENDED


// статус опроса счетчиков
typedef enum
{
  ST4_NONE              = 0,
  ST4_OK                = 1,
  ST4_NOTSUPPORTED      = 2,
  ST4_NOTPRESENTED      = 3,
  ST4_BADDIGITAL        = 0x80,
  ST4_BADFLASH          = 0x81,
  ST4_MODEM_LINK        = 0x82,
  ST4_DISABLED          = 0x83
} status;


// значение счетчика по тарифам
typedef struct
{
  double        mpdbValuesT[bTARIFFS];
} value5a;


// значение счетчика по тарифам (прямой опрос)
typedef struct
{
  value5a       stValue;
  time          tiUpdate;
  bool          boSuccess;
  uint          cwSuccess,cwError;
} value5b;


//
typedef struct
{
  status        bStatus;
  double        dbValue;
  time          tiUpdate;
} value6;


//
typedef struct
{
  status        bStatus;
  double        mpdbValuesT[bTARIFFS];
  time          tiUpdate;
} value4t;


// время
typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
} stamp;


// значение счетчика на момент времени
typedef struct
{
  double        dbValue;
  stamp         stValue;
} diagram;


#endif
