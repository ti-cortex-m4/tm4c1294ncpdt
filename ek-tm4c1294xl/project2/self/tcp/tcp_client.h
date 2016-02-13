/*------------------------------------------------------------------------------
TCP_CLIENT.H


------------------------------------------------------------------------------*/

extern void TelnetInit(void);

err_t TCPClientConnect(ulong dwRemoteIP, uint wRemotePort);
