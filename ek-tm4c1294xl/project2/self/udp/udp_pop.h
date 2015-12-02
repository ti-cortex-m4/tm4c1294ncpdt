/*------------------------------------------------------------------------------
UDP_POP.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t PopArgument(struct pbuf *p, uint *pw);
err_t PopSuffix(struct pbuf *p, uint *pw);
