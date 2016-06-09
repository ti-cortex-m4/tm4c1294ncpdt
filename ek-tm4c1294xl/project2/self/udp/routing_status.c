/*------------------------------------------------------------------------------
routing_status,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/printf.h"
#include "../uart/io_mode.h"
#include "../uart/serial.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_cmd.h"
#include "routing_status.h"



static const uchar CONTENT_SIZE = 7;

static const char * const szSerialPort = "Serial Port";
static const char * const szIOMode = "RS-485 Direction (0 - unknown, 1 - input, 2 - output)";
static const char * const szVariables = "Variables";

static const char * const szHead = "<head><style type='text/css'>table{border-collapse:collapse;font:11px arial;background-color:#C0C0C0}td.head{color:white;background-color:#648CC8}</style></head>";
static const char * const szBodyStart = "<body><table width=100% bgcolor=#C0C0C0 border='1'>";
static const char * const szHeaderS = "<tr><td colspan=2 class='head'>%s</td></tr>";
static const char * const szRowSU = "<tr><td>%s</td><td>%u</td></tr>";
static const char * const szBodyEnd = "</table></body>";



bool IsRoutingStatusSize(struct pbuf *p) { // TODO
  if (IsCmd(p,"CU@1")) return true;
  if (IsCmd(p,"CU@2")) return true;
  if (IsCmd(p,"CU@3")) return true;
  if (IsCmd(p,"CU@4")) return true;
  if (IsCmd(p,"CU@5")) return true;
  return false;
}


err_t GetRouingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  return CmdCharDec(pcb,p,addr,port,broadcast,CONTENT_SIZE);
}



bool IsRoutingStatusContent(struct pbuf *p) {
  return IsCmd(p, "FU");
}


err_t GetRouingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  uchar ibStart = 0xFF;
  if (!IsPrefix(p, "FU", &ibStart)) {
    CONSOLE("WARNING routing mode: not found \"FU\"\n");
    return ERR_OK;
  }

  uint wIdx = 0xFF;
  err_t err = PopInt2(p, &wIdx, ibStart, 10, '@');
  if (err != ERR_OK) {
    CONSOLE("WARNING bad routing mode index\n");
    return ERR_OK;
  }

  ibStart = 0xFF;
  if (!IsChar(p, '@', &ibStart)) {
    CONSOLE("WARNING routing mode: not found '@'\n");
    return ERR_OK;
  }

  uchar bPort = 0xFF;
  err = PopCharDec(p, &bPort, ibStart);
  if (err != ERR_OK) {
    CONSOLE("WARNING bad routing mode port\n");
    return ERR_OK;
  }

  if (!(bPort >= 1) && (bPort <= UART_COUNT)) {
    CONSOLE("WARNING bad routing mode port %u\n",bPort);
    return ERR_OK;
  }

  uchar u = bPort-1;
  ASSERT(u < UART_COUNT);

  switch (wIdx) {
    case 0: CmdString(pcb,p,addr,port,broadcast,szHead); break;
    case 1: CmdString(pcb,p,addr,port,broadcast,szBodyStart); break;
    case 2: CmdBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szSerialPort)); break;
    case 3: CmdBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szIOMode, GetIOMode(u))); break;
    case 4: CmdBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szVariables)); break;
    case 5: CmdBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mwTxSize", mwTxSize[u])); break;
    case 6: CmdString(pcb,p,addr,port,broadcast,szBodyEnd); break;
    default: CONSOLE("WARNING unknown routing mode index %u\n", wIdx); break;
  }

  return ERR_OK;
}
