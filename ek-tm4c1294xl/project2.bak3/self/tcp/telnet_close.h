/*------------------------------------------------------------------------------
telnet_close.h


------------------------------------------------------------------------------*/

err_t TelnetCloseClient(uint8_t ucSerialPort);
void TelnetCloseServer(struct tcp_pcb *pcb, uint8_t ucSerialPort);
