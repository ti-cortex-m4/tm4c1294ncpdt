/*------------------------------------------------------------------------------
udp_pop.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"
#include "../kernel/wrappers.h"



uint2 PopInt(struct pbuf *p, const uchar ibStart, const uchar bRadix, const uchar cBorder);
uint2 PopIntDec(struct pbuf *p, const uchar ibStart);
uint2 PopIntHex(struct pbuf *p, const uchar ibStart);

uchar2 PopChar(struct pbuf *p, const uchar ibStart, const uchar bRadix, const uchar cBorder);
uchar2 PopCharDec(struct pbuf *p, const uchar ibStart);

ulong2 PopIP(struct pbuf *p, const uchar ibStart);
err_t PopBuff(struct pbuf *p, char *szBuff, const uchar bSize, const uchar ibStart);
uint2 PopSuffix(struct pbuf *p);
