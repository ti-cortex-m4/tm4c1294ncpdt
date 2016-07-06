/*------------------------------------------------------------------------------
modem.h


------------------------------------------------------------------------------*/

void InitModem(void);

bool IsModemCommandMode(const char u);
void ProcessModemCommandMode(const char u, const char b);

void RunModem(const char u);
