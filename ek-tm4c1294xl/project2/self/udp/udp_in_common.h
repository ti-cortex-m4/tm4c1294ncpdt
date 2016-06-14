/*------------------------------------------------------------------------------
udp_in_common.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



bool IsCmd(struct pbuf *p, const char *pcszCmd);
uchar2 GetCmdEndIndex(struct pbuf *p, const char *pcszCmd);
uchar2 GetBorderIndex(struct pbuf *p, uchar bBorder);
