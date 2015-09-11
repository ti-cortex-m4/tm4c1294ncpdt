/*------------------------------------------------------------------------------
SLAVE_MODEM.H


-----------------------------------------------------------------------------*/

void    InitSlaveModem(void);
void    ResetSlaveModem(void);

void    ResetSendAT(uchar  ibPrt);
void    ResetSendAT_All(void);

void    RunSlaveModem_All(void);

void    SlaveModem_1Hz(void);

void    OutSlaveModem(void);
