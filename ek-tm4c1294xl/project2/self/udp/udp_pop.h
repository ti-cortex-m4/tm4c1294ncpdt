/*------------------------------------------------------------------------------
UDP_POP.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t PopIntArgument(struct pbuf *p, uint *pw);
err_t PopStringArgument(struct pbuf *p, char *sz, uchar  bSize);
err_t PopSfx(struct pbuf *p, uint *pw);
