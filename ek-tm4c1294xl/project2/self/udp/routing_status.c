/*------------------------------------------------------------------------------
routing_status.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_cmd.h"
#include "routing_status.h"



static const uchar ROUTING_STATUS_SIZE = 5;

static const char * const szContent1 = "<head><style type='text/css'>table{border-collapse:collapse;font:11px arial;background-color:#C0C0C0}td.head{color:white;background-color:#648CC8}</style></head>";
static const char * const szContent2 = "<body><table width=100% bgcolor=#C0C0C0 border='1'>";
static const char * const szContent3 = "<tr><td colspan=2 class='head'>Routing Buffers</td></tr>";
static const char * const szContent4 = "<tr><td>Ethernet -> Serial (data/capacity)</td><td>0/1263</td></tr>";
static const char * const szContent5 = "</table></body>";



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

  CONSOLE("ibStart %u\n", ibStart);

    uint bIdx = 0;
    err_t err = PopInt2(p, &bIdx, ibStart, 10);

    CONSOLE("index %u\n", bIdx);

    switch (bIdx)
    {
      case 0: CmdString(pcb,p,addr,port,broadcast,szContent1); break;
      case 1: CmdString(pcb,p,addr,port,broadcast,szContent2); break;
      case 2: CmdString(pcb,p,addr,port,broadcast,szContent3); break;
      case 3: CmdString(pcb,p,addr,port,broadcast,szContent4); break;
      case 4: CmdString(pcb,p,addr,port,broadcast,szContent5); break;
      default: CONSOLE("ERROR unknown index %u\n", bIdx); ASSERT(false); break; // TODO
    }

    return ERR_OK;
  }

  ASSERT(false);
  return ERR_OK;
}
