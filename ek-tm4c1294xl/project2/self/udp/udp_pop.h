/*------------------------------------------------------------------------------
UDP_POP.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t PopIntArgument(struct pbuf *p, uint *pw);
err_t PopStringNameArgument(struct pbuf *p, char szName[NAME_SIZE]);
err_t PopSuffix(struct pbuf *p, uint *pw);
