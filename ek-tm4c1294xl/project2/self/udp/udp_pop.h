/*------------------------------------------------------------------------------
UDP_POP,H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"
#include "../kernel/wrappers.h"



uint2 PopInt(struct pbuf *p, uchar ibStart, uchar bRadix, uchar cBorder);
uint2 PopIntDec(struct pbuf *p, const uchar ibStart);
uint2 PopIntHex(struct pbuf *p, const uchar ibStart);
uchar2 PopCharDec(struct pbuf *p, const uchar ibStart);
ulong2 PopIP(struct pbuf *p, const uchar ibStart);
err_t PopString(struct pbuf *p, char *sz, const uchar bSize, const uchar ibStart);
uint2 PopSfx(struct pbuf *p);
