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
#include "../uart/modem.h"
#include "../tcp/tcp_errors.h"
#include "../tcp/telnet.h"
#include "udp_log.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_in_common.h"
#include "udp_out_common.h"
#include "routing_status.h"



static uchar            ibRoutingStatus = 0;


static message szSerialPort = "Serial Port";
static message szIOMode = "RS-485 Direction (0 - unknown, 1 - input, 2 - output)";
static message szVariables = "Variables";
static message szRuntime = "Runtime";
static message szTCPCounters = "TCP Counters";
static message szErrorCounters = "Error Counters";
static message szUptime = "Working time (since last restart)";
static message szWatchdogReset = "Last restart type (0 - power-up, 1 - watchdog)";

static message szHead = "<head><style type='text/css'>table{border-collapse:collapse;font:11px arial;background-color:#C0C0C0}td.head{color:white;background-color:#648CC8}</style></head>";
static message szBodyStart = "<body><table width=100% bgcolor=#C0C0C0 border='1'>";
static message szHeaderS = "<tr><td colspan=2 class='head'>%s</td></tr>";
static message szRowSU = "<tr><td>%s</td><td>%u</td></tr>";
static message szRowClock = "<tr><td>%s</td><td>%u %02u:%02u:%02u</td></tr>";
static message szRowTCPError = "<tr><td>%s</td><td>%d, %u, %u %02u:%02u:%02u</td></tr>";
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
  uchar bSize;
  switch (ibRoutingStatus) {
    case 0: bSize = 17; break;
    case 1: bSize = 14; break;
    default: bSize = IsCmd(p,"CU@1") ? 15 : 3; break;
  }

  CONSOLE("GetRouingStatusSize ibRoutingStatus=%u bSize=%u\n", ibRoutingStatus, bSize);
  return OutCharDec(pcb,p,addr,port,broadcast,bSize);
}



bool IsRoutingStatusContent(struct pbuf *p) {
  return IsCmd(p, "FU");
}



static err_t OutUptime(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  date_t days = SecondsToDate(GetClockSeconds());
  return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowClock, szUptime, days.wDays, days.bHours, days.bMinutes, days.bSeconds));
}

static err_t OutTCPError(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *pcszOperation, const uchar u, const uchar op) {
  ASSERT(u < UART_COUNT);
  ASSERT(op < TCP_OPERATIONS);

  date_t days = SecondsToDate(mdwErrTCPClockSeconds[u][op]);

  return OutBuff(pcb,p,addr,port,broadcast,
      BuffPrintF(szRowTCPError, pcszOperation,
          mwErrTCPErrors[u][op],
          mcwErrTCPCounters[u][op],
          days.wDays, days.bHours, days.bMinutes, days.bSeconds
      )
  );
}



static void NextRouingStatus(const uchar u) {
  CONSOLE("NextRouingStatus1 ibRoutingStatus=%u u=%u\n", ibRoutingStatus, u);

  if (u == UART_COUNT-1) {
    ibRoutingStatus = ++ibRoutingStatus % 3;
    CONSOLE("NextRouingStatus2 ibRoutingStatus=%u u=%u\n", ibRoutingStatus, u);
  }
}


static err_t GetRouingStatusContent1(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  switch (wIdx) {
    case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
    case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);

    case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szSerialPort));
    case 3: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szIOMode, GetIOMode(u)));

    case 4: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szRuntime));
    case 5: return OutUptime(pcb,p,addr,port,broadcast);
    case 6: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szWatchdogReset, fWatchdogReset));

    case 7: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szVariables));
    case 8: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mcwUARTTxOut", mcwUARTTxOut[u]));

    case 9: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szVariables));
    case 10: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbModemMode", mbModemMode[u]));
    case 11: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbInputMode", mbInputMode[u]));
    case 12: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbEscapeCnt", mbEscapeCnt[u]));
    case 13: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbEscapeMode", mbEscapeMode[u]));

    case 14: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szVariables));
    case 15: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "tTCPState", g_sState[u].eTCPState));

    case 16: NextRouingStatus(u); return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
    default: WARNING("routing status 1: wrong index %u\n", wIdx); return GetError();
  }
}

static err_t GetRouingStatusContent2(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  switch (wIdx) {
    case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
    case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
    case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szTCPCounters));
    case 3: return OutTCPError(pcb,p,addr,port,broadcast,"HANDLER_ERROR",u,0);
    case 4: return OutTCPError(pcb,p,addr,port,broadcast,"HANDLER_CONNECTED",u,1);
    case 5: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_NEW_LISTEN",u,2);
    case 6: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_BIND_LISTEN",u,3);
    case 7: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_NEW_OPEN",u,4);
    case 8: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CONNECT_OPEN",u,5);
    case 9: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CONNECT_POLL",u,6);
    case 10: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CLOSE_CONNECTED",u,7);
    case 11: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CLOSE_RECEIVE",u,8);
    case 12: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CLOSE_CLOSE",u,9);
    case 13: NextRouingStatus(u); return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
    default: WARNING("routing status 2: wrong index %u\n", wIdx); return GetError();
  }
}

static err_t GetRouingStatusContent3(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  if (u == 0) {
    switch (wIdx) {
      case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
      case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
      case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, szErrorCounters));
      case 3: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrPrintfOverflow", cwErrPrintfOverflow));
      case 4: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDPushCharOverflow", cwErrUPDPushCharOverflow));
      case 5: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDPushNumbersOverflow", cwErrUPDPushNumbersOverflow));
      case 6: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDOutPbufAlloc", cwErrUPDOutPbufAlloc));
      case 7: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDOutSendUnicast", cwErrUPDOutSendUnicast));
      case 8: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUPDOutSendBroadcast", cwErrUPDOutSendBroadcast));
      case 9: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUDPLogPbufAlloc", cwErrUDPLogPbufAlloc));
      case 10: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrUDPLogSend", cwErrUDPLogSend));
      case 11: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrSettingsInitStorage", cwErrSettingsInitStorage));
      case 12: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrSettingsSaveEntity", cwErrSettingsSaveEntity));
      case 13: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "cwErrSettingsLoadIP", cwErrSettingsLoadIP));
      case 14: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
      default: WARNING("routing status 3: wrong index %u\n", wIdx); return GetError();
    }
  } else {
    switch (wIdx) {
      case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
      case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
      case 2: NextRouingStatus(u); return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
      default: WARNING("routing status 3: wrong index %u\n", wIdx); return GetError();
    }
  }
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

//  CONSOLE("GetRouingStatusContent ibRoutingStatus=%u wIdx=%u u=%u\n", ibRoutingStatus, wIdx, u);

  switch (ibRoutingStatus) {
    case 0: return GetRouingStatusContent1(pcb,p,addr,port,broadcast,wIdx,u);
    case 1: return GetRouingStatusContent2(pcb,p,addr,port,broadcast,wIdx,u);
    default: return GetRouingStatusContent3(pcb,p,addr,port,broadcast,wIdx,u);
  }
}
