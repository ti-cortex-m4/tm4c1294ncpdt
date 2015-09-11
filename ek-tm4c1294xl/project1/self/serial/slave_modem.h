/*------------------------------------------------------------------------------
SLAVE_MODEM.H


-----------------------------------------------------------------------------*/

void    InitSlaveModem(void);
void    ResetSlaveModem(void);

void    InitSerial_SlaveModem(uchar  ibPrt);
void    UARTIntHandler_SlaveModem(uchar  ibPrt);
void    ResetSendAT(void);

void    SlaveModem_1Hz(void);
