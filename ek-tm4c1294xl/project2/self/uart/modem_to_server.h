/*------------------------------------------------------------------------------
modem_to_server.h


------------------------------------------------------------------------------*/

#ifndef __MODEM_TO_SERVER_H__
#define __MODEM_TO_SERVER_H__


typedef enum
{
  MTS_BEGIN = 0,
  MTS_TIMEOUT = 1,
} mts_t;



void InitModemToServer(void);
void ProcessModemToServerData(const uchar u);
void ModemToServer_1Hz(void);
void RunModemToServer(const uchar u);


#endif
