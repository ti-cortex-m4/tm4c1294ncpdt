/*------------------------------------------------------------------------------
modem.h


------------------------------------------------------------------------------*/

void InitModem(void);

bool IsModemCommandMode(const uchar u);
void ProcessModemCommandMode(const uchar u, const uchar b);

void RunModem(const uchar u);
