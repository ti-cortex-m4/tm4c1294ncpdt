/*------------------------------------------------------------------------------
udp_out_common,h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t CmdString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *pcsz);
err_t CmdBuff(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, buff bf);
err_t CmdCharDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uchar b);
err_t CmdIntDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uint w);
err_t CmdIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const ulong dw);

bool IsCmd(struct pbuf *p, const char *szCmd);
bool IsPrefix(struct pbuf *p, const char *szCode, uchar *pibStart);
bool IsChar(struct pbuf *p, uchar bChar, uchar *pibStart);
