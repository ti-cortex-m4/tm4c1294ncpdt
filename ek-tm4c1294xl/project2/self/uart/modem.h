/*------------------------------------------------------------------------------
modem.h


------------------------------------------------------------------------------*/

void InitModem(void);

bool IsModemModeCommand(const uchar u);
void ProcessModemModeCommand(const uchar u, const uchar b);

void RunModem(const uchar u);

void ModemConnected(const uchar u);

void Modem_10Hz(void);
void ProcessModemModeData(const uchar u, const uchar b);
