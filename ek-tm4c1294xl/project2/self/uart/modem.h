/*------------------------------------------------------------------------------
modem.h


------------------------------------------------------------------------------*/

extern volatile modem_mode_t   mbModemMode[UART_COUNT];
extern volatile input_mode_t   mbInputMode[UART_COUNT];

extern volatile uchar          mbEscapeCnt[UART_COUNT];
extern volatile escape_mode_t  mbEscapeMode[UART_COUNT];



void InitModem(void);

bool IsModemModeCommand(const uchar u);
void ProcessModemModeCommand(const uchar u, const uchar b);

void RunModem(const uchar u);

void ModemConnected(const uchar u);

void Modem_10Hz(void);
void ProcessModemModeData(const uchar u, const uchar b);
