/*------------------------------------------------------------------------------
modem.h


------------------------------------------------------------------------------*/

#ifndef __MODEM_H__
#define __MODEM_H__


typedef enum
{
  MODEM_MODE_COMMAND = 0,
  MODEM_MODE_DATA = 1,
} modem_mode_t;


typedef enum
{
  INPUT_MODE_BEGIN = 0,
  INPUT_MODE_DATA = 1,
  INPUT_MODE_READY = 2,
} input_mode_t;


typedef enum
{
  ESCAPE_MODE_BEGIN = 0,
  ESCAPE_MODE_DATA = 1,
  ESCAPE_MODE_PAUSE_BEFORE = 2,
  ESCAPE_MODE_PLUS_1 = 3,
  ESCAPE_MODE_PLUS_2 = 4,
  ESCAPE_MODE_PLUS_3 = 5,
  ESCAPE_MODE_PAUSE_AFTER = 6,
} escape_mode_t;



extern volatile modem_mode_t   mbModemMode[UART_COUNT];
extern volatile input_mode_t   mbInputMode[UART_COUNT];

extern volatile uchar          mbEscapeCnt[UART_COUNT];
extern volatile escape_mode_t  mbEscapeMode[UART_COUNT];



void InitModem(void);

bool IsModemModeCommand(const uchar u);
void ProcessModemModeCommand(const uchar u, const uchar b);
void ProcessModemModeData(const uchar u, const uchar b);
void Modem_10Hz(void);

void RunModem(const uchar u);

void ModemConnected(const uchar u);


#endif
