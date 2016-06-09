/*------------------------------------------------------------------------------
routing_status.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_cmd.h"
#include "routing_status.h"



static const uchar ROUTING_STATUS_SIZE = 3;

static const char * const szContent1 = "  ";
static const char * const szContent2 = "  ";
static const char * const szContent3 = "  ";



bool IsRoutingStatusSize(struct pbuf *p) {
  if (IsCmd(p,"CU@1")) return true;
  if (IsCmd(p,"CU@2")) return true;
  if (IsCmd(p,"CU@3")) return true;
  if (IsCmd(p,"CU@4")) return true;
  if (IsCmd(p,"CU@5")) return true;
  return false;
}


err_t GetRouingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  return CmdCharDec(pcb,p,addr,port,broadcast,ROUTING_STATUS_SIZE);
}



static bool IsPrefix(struct pbuf *p, const char *szCode, uchar *pibStart)
{
  uchar *pb = p->payload;
  uchar i = 0;

  while (*szCode)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCode++) return false;
  }

  *pibStart = i;
  return true;
}


bool IsRoutingStatusContent(struct pbuf *p) {
  uchar ibStart = 0xFF;
  return IsPrefix(p, "FU", &ibStart);
}



err_t GetRouingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  uchar ibStart = 0xFF;
  if (IsPrefix(p, "FU", &ibStart)) {
    uchar bIdx = 0;
    err_t err = PopCharDec(p, &bIdx, ibStart);

    switch (bIdx)
    {
      case 0: PushString(szContent1); break;
      case 1: PushString(szContent2); break;
      case 2: PushString(szContent3); break;
      default: CONSOLE("ERROR unknown index %u\n", bIdx); ASSERT(false); break; // TODO
    }
  }

  ASSERT(false);
  return ERR_OK;
}
