/*------------------------------------------------------------------------------
server_to_modem.h


------------------------------------------------------------------------------*/

#ifndef __SERVER_TO_MODFM_H__
#define __SERVER_TO_MODFM_H__


typedef enum
{
  FM_BEGIN = 0,
  FM_PAUSE_BEFORE = 1,
  FM_DATA = 2,
  FM_DATA_FINISH = 3,
  FM_PAUSE_AFTER = 4,
} fallback_mode_t;


#endif
