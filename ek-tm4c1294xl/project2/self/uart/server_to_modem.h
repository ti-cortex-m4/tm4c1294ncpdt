/*------------------------------------------------------------------------------
server_to_modem.h


------------------------------------------------------------------------------*/

#ifndef __SERVER_TO_MODEM_H__
#define __SERVER_TO_MODEM_H__


typedef enum
{
  STM_BEGIN = 0,
  STM_PAUSE_BEFORE = 1,
  STM_DATA = 2,
  STM_DATA_FINISH = 3,
  STM_PAUSE_AFTER = 4,
} stm_t;


void InitServerToModem(void);
void ProcessServerToModemData(const uchar u, const uchar b);
void ServerToModem_10Hz(void);
void RunServerToModem(const uchar u);


#endif
