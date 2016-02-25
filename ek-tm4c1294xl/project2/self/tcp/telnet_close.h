/*------------------------------------------------------------------------------
telnet_close.h


------------------------------------------------------------------------------*/

err_t TelnetCloseClient(uint8_t ucSerialPort);
err_t TelnetCloseServer(struct tcp_pcb *pcb, uint8_t ucSerialPort);
