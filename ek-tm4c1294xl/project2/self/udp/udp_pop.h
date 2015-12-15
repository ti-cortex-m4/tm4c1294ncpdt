/*------------------------------------------------------------------------------
UDP_POP.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t PopCharHex(struct pbuf *p, uchar *pb, uchar ibStart);
err_t PopIntHex(struct pbuf *p, uint *pw, uchar ibStart);
err_t PopIP(struct pbuf *p, ulong *pdw);
err_t PopString(struct pbuf *p, char *sz, uchar  bSize);
err_t PopSfx(struct pbuf *p, uint *pw);
