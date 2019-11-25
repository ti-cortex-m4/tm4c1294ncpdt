/*------------------------------------------------------------------------------
include35.h


------------------------------------------------------------------------------*/

#ifndef __INCLUDE35
#define __INCLUDE35


#define NNCL2_DATA_SET  17
#define NNCL2_DATA_GET  18
#define NNCL2_TIME      20
#define NNCL2_ERROR     31


typedef enum
{
  R35_REPEAT_LAST_QUERY    = 0,

  R35_REPEAT_START         = 1,
  R35_REPEAT_ERROR_TIMEOUT = 2,

  R35_ROUTER_ERROR_SIZE    = 3,
  R35_ROUTER_ERROR_ERROR   = 4,
  R35_ROUTER_ERROR_COMMAND = 5,

  R35_SENSOR_SUCCESS       = 6,
  R35_SENSOR_FAILURE       = 7
} result35;


typedef enum
{
  A35_WAIT      = 0,
  A35_SUCCESS   = 1,
  A35_ERROR     = 2,
  A35_BREAK     = 3
} action35;


typedef struct
{
  bool          fLog;
  result35      enResult;
  action35      enAction;
  uint          wData;
} event35;


typedef struct
{
  time          tiNow;
  result35      enResult;
  uint          wData;
} log35;


typedef struct
{
  time          tiNow;
  uint          wCounter;
} counter35;


#endif
