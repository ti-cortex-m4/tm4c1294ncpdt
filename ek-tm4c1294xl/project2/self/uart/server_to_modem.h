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


void InitServerToModem(void);
bool IsServerToModem(const uchar u);
void ProcessServerToModemData(const uchar u, const uchar b);
void ServerToModem_10Hz(void);
void RunServerToModem(const uchar u);


#endif
