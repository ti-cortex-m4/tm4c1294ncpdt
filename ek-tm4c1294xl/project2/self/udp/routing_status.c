/*------------------------------------------------------------------------------
routing_status.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/printf.h"
#include "../kernel/clock.h"
#include "../kernel/settings.h"
#include "../uart/io_mode.h"
#include "../uart/serial.h"
#include "udp_log.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_in_common.h"
#include "udp_out_common.h"
#include "routing_status.h"



#define ROUTING_STATUS_SIZE  7
#define ROUTING_DEBUG_SIZE   14


static message szSerialPort = "Serial Port";
static message szIOMode = "RS-485 Direction (0 - unknown, 1 - input, 2 - output)";
static message szVariables = "Variables";
static message szRuntime = "Runtime";
static message szUptime = "Working time after last restart";
static message szWatchdogReset = "Last restart type (0 - power-up, 1 - watchdog)";

static message szHead = "<head><style type='text/css'>table{border-collapse:collapse;font:11px arial;background-color:#C0C0C0}td.head{color:white;background-color:#648CC8}</style></head>";
static message szBodyStart = "<body><table width=100% bgcolor=#C0C0C0 border='1'>";
static message szHeaderS = "<tr><td colspan=2 class='head'>%s</td></tr>";
static message szRowSU = "<tr><td>%s</td><td>%u</td></tr>";
static message szRowClock = "<tr><td>%s</td><td>%u day(s) %02u:%02u:%02u</td></tr>";
static message szBodyEnd = "</table></body>";



bool IsRoutingStatusSize(struct pbuf *p) {
  if (IsCmd(p,"CU@1")) return true;
  if (IsCmd(p,"CU@2")) return true;
  if (IsCmd(p,"CU@3")) return true;
  if (IsCmd(p,"CU@4")) return true;
  if (IsCmd(p,"CU@5")) return true;
  return false;
}


err_t GetRouingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  uchar bSize = ROUTING_STATUS_SIZE;

  if (IsCmd(p,"CU@5"))
    bSize += ROUTING_DEBUG_SIZE;

  return OutCharDec(pcb,p,addr,port,broadcast,bSize);
}



bool IsRoutingStatusContent(struct pbuf *p) {
  return IsCmd(p, "FU");
}


static void OutUptime(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  ulong dwSeconds = GetClockSeconds();
  uint wDays = dwSeconds / SECONDS_IN_DAY;
  dwSeconds %= SECONDS_IN_DAY;
  uchar bHours = dwSeconds / SECONDS_IN_HOUR;
  dwSeconds %= SECONDS_IN_HOUR;
  uchar bMinutes = dwSeconds / SECONDS_IN_MINUTE;
  dwSeconds %= SECONDS_IN_MINUTE;

  OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowClock, szUptime, wDays, bHours, bMinutes, dwSeconds));
}


err_t GetRouingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  uchar2 ibStart = GetCmdEndIndex(p, "FU");
  if (InvalidChar2(ibStart)) {
    WARNING("routing status: not found 'FU'\n");
    return ibStart.err;
  }

  uint2 w2 = PopInt(p, ibStart.b, 10, '@');
  if (InvalidInt2(w2)) {
    WARNING("routing status: wrong index\n");
    return w2.err;
  }
  uint wIdx = w2.w;

  ibStart = GetBorderIndex(p, '@');
  if (InvalidChar2(ibStart)) {
    WARNING("routing status: not found '@'\n");
    return ibStart.err;
  }

  uchar2 b2 = PopCharDec(p, ibStart.b);
  if (InvalidChar2(b2)) {
    WARNING("routing status: wrong port\n");
    return b2.err;
  }

  uchar bPort = b2.b;
  if (!(bPort >= 1) && (bPort <= UART_COUNT)) {
    WARNING("routing status: wrong port %u\n", bPort);
    return GetError();
  }

  uchar u = bPort-1;
  ASSERT(u < UART_COUNT);

  switch (wIdx) {
    case 0: OutString(pcb,p,addr,port,broadcast,szHead); break;
    case 1: OutString(pcb,p,addr,port,broadcast,szBodyStart); break;
    case 2: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szSerialPort)); break;
    case 3: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szIOMode, GetIOMode(u))); break;
    case 4: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szVariables)); break;
    case 5: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mwTxSize", mwTxSize[u])); break;
  }

  if (u != UART_COUNT-1) {
    switch (wIdx) {
      case 6: OutString(pcb,p,addr,port,broadcast,szBodyEnd); break;
    }
    if (wIdx >= ROUTING_STATUS_SIZE) {
      WARNING("routing status: wrong index %u\n", wIdx);
    }
  } else {
    switch (wIdx) {
      case 6: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szRuntime)); break;
      case 7: OutUptime(pcb,p,addr,port,broadcast); break;
      case 8: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szWatchdogReset, fWatchdogReset)); break;
      case 9: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szVariables)); break;
      case 10: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrPrintfOverflow", cwErrPrintfOverflow)); break; // TODO define
      case 11: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDPushCharOverflow", cwErrUPDPushCharOverflow)); break;
      case 12: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDPushNumbersOverflow", cwErrUPDPushNumbersOverflow)); break;
      case 13: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDOutPbufAlloc", cwErrUPDOutPbufAlloc)); break;
      case 14: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDOutSendUnicast", cwErrUPDOutSendUnicast)); break;
      case 15: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDOutSendBroadcast", cwErrUPDOutSendBroadcast)); break;
      case 16: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUDPLogPbufAlloc", cwErrUDPLogPbufAlloc)); break;
      case 17: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUDPLogSend", cwErrUDPLogSend)); break;
      case 18: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrSettingsStorageInit", cwErrSettingsStorageInit)); break;
      case 19: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrSettingsIPLoad", cwErrSettingsIPLoad)); break;
      case 20: OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrSettingsEntitySave", cwErrSettingsEntitySave)); break;
      case 21: OutString(pcb,p,addr,port,broadcast,szBodyEnd); break;
    }
    if (wIdx >= ROUTING_STATUS_SIZE + ROUTING_DEBUG_SIZE) {
      WARNING("routing status: wrong debug index %u\n", wIdx);
    }
  }

  return GetSuccess();
}
