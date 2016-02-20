/*------------------------------------------------------------------------------
UDP_POP,H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t PopIntDec(struct pbuf *p, uint *pw, const uchar ibStart);
err_t PopIntHex(struct pbuf *p, uint *pw, const uchar ibStart);
err_t PopCharDec(struct pbuf *p, uchar *pb, const uchar ibStart);
err_t PopIP(struct pbuf *p, ulong *pdw, const uchar ibStart);
err_t PopString(struct pbuf *p, char *sz, const uchar bSize, const uchar ibStart);
err_t PopSfx(struct pbuf *p, uint *pw);
