/*------------------------------------------------------------------------------
UDP_PUSH.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t InitPush(struct pbuf **pp, uchar bSize);
void PushChar(uchar b);
void PushIntLtl(uint w);
void PushLongLtl(ulong dw);
void PushIPCtrl(ulong dw);
void PushString(const char *sz);
void PushCode(uint wCode);
void PushMAC(uchar *pbMAC);
uchar GetPushSize(void);
