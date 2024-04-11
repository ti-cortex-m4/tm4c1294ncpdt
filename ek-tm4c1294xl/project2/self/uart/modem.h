/*------------------------------------------------------------------------------
modem.h


------------------------------------------------------------------------------*/

#ifndef __MODEM_H__
#define __MODEM_H__


typedef enum
{
  MM_COMMAND = 0,
  MM_DATA = 1,
} modem_mode_t;


typedef enum
{
  IM_BEGIN = 0,
  IM_DATA = 1,
  IM_READY = 2,
} input_mode_t;


typedef enum
{
  EM_BEGIN = 0,
  EM_PAUSE_BEFORE = 1,
  EM_PLUS_1 = 2,
  EM_PLUS_2 = 3,
  EM_PLUS_3 = 4,
  EM_PAUSE_AFTER = 5,
} escape_mode_t;


typedef enum
{
  DC_UNKNOWN = 0,
  DC_NORMALLY = 1,
  DC_TIMEOUT = 2,
  DC_REMOTE = 3,
} disconnect_t;


extern volatile modem_mode_t   mbModemMode[UART_COUNT];
extern volatile input_mode_t   mbInputMode[UART_COUNT];

extern volatile uchar          mbEscapeCnt[UART_COUNT];
extern volatile escape_mode_t  mbEscapeMode[UART_COUNT];



void InitModem(void);

void ModemSetVerbose(const bool f);
bool IsModem(const uchar u);
bool IsModemModeCommand(const uchar u);
bool IsModemModeData(const uchar u);
void ProcessModemModeCommand(const uchar u, const uchar b);
void ProcessModemModeData(const uchar u, const uchar b);
void Modem_10Hz(void);

void ModemOutSetRoutingModeModem(const uchar u);
void ModemOutSetRoutingModeServer(const uchar u);
void RunModem(const uchar u);

void ModemConnected(const uchar u);
void ModemConnectFailed(const uchar u, const err_t err);
void ModemDisconnectedByTimeout(const uchar u);


#endif
