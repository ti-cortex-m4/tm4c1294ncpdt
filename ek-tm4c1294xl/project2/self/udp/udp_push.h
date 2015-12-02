/*------------------------------------------------------------------------------
UDP_PUSH.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t InitPush(struct pbuf **pp, uchar bSize);
void PushChar(uchar b);
void PushIntLtl(uint w);
void PushLongLtl(ulong dw);
void PushString(const char *sz);
uchar PushIntHex(uint w);
uchar PushCharDec(uchar b);
void PushIPString(ulong dw);
void PushSuffix(uint w);
void PushMAC(uchar *pbMAC);
uchar GetPushSize(void);
