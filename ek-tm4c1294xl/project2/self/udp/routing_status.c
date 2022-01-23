/*------------------------------------------------------------------------------
routing_status.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/rom.h"
#include "../kernel/log.h"
#include "../kernel/printf.h"
#include "../kernel/clock.h"
#include "../kernel/settings.h"
#include "../uart/io_mode.h"
#include "../uart/serial.h"
#include "../uart/modem.h"
#include "../tcp/tcp_errors.h"
#include "../tcp/telnet.h"
#include "lwip/stats.h"
#include "udp_log.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_in_common.h"
#include "udp_out_common.h"
#include "routing_status.h"


static uchar            ibRoutingStatus = 0;


static message szIOMode = "RS-485 Direction (0 - unknown, 1 - input, 2 - output)";
static message szUptime = "Working time (since last restart)";
static message szVersion = "Version";
static message szWatchdogReset = "Last restart type (0 - power-up, 1 - watchdog)";

static message szHead = "<head><style type='text/css'>table{border-collapse:collapse;font:11px arial;background-color:#C0C0C0}td.head{color:white;background-color:#648CC8}</style></head>";
static message szBodyStart = "<body><table width=100% bgcolor=#C0C0C0 border='1'>";
static message szHeaderS = "<tr><td colspan=2 class='head'>%s</td></tr>";
static message szRowS08X = "<tr><td>%s</td><td>0x%08x</td></tr>";
static message szRowSU = "<tr><td>%s</td><td>%u</td></tr>";
static message szRowSIP = "<tr><td>%s</td><td>%u.%u.%u.%u</td></tr>";
static message szRowClock = "<tr><td>%s</td><td>%u %02u:%02u:%02u</td></tr>";
static message szRowVersion = "<tr><td>%s</td><td>%u.%u.%u.%04X %02u.%02u.%02u %02u:%02u:%02u</td></tr>";
static message szRowTCPError = "<tr><td>%s</td><td>%d, %u, %u %02u:%02u:%02u</td></tr>";
static message szMemStatsHeader = "<tr><td class='head'>Memory statistics</td><td class='head'>available</td><td class='head'>used</td><td class='head'>maximum</td><td class='head'>errors</td></tr>";
static message szMemStatsRow = "<tr><td>MEM %s</td><td>%u</td><td>%u</td><td>%u</td><td>%u</td></tr>";
static message szBodyEnd = "</table></body>";



void NextRoutingStatus(void) {
  ibRoutingStatus = ++ibRoutingStatus % 6;
}



#ifndef SINGLE_UART

bool IsRoutingStatusSize(struct pbuf *p) {
  if (IsCmd(p,"CU@1")) return true;
  if (IsCmd(p,"CU@2")) return true;
  if (IsCmd(p,"CU@3")) return true;
  if (IsCmd(p,"CU@4")) return true;
  if (IsCmd(p,"CU@5")) return true;
  return false;
}


err_t GetRoutingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
  uchar bSize;
  switch (ibRoutingStatus) {
    case 0: bSize = IsCmd(p,"CU@1") ? 7 : 3; break;
    case 1: bSize = 11; break;
    case 2: bSize = 14; break;
    case 3: bSize = 16; break;
    case 4: bSize = IsCmd(p,"CU@1") ? 15 : 3; break;
    default: bSize = IsCmd(p,"CU@1") ? 12 : 3; break;
  }

  return OutCharDec(pcb,p,addr,port,broadcast,bSize);
}

#else

bool IsRoutingStatusSize(struct pbuf *p) {
  if (IsCmd(p,"CU")) return true;
  return false;
}


err_t GetRoutingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
  uchar bSize;
  switch (ibRoutingStatus) {
    case 0: bSize = IsCmd(p,"CU@1") ? 7 : 3; break;
    case 1: bSize = 11; break;
    case 2: bSize = 14; break;
    case 3: bSize = 16; break;
    case 4: bSize = IsCmd(p,"CU") ? 15 : 3; break;
    default: bSize = IsCmd(p,"CU") ? 12 : 3; break;
  }

  return OutCharDec(pcb,p,addr,port,broadcast,bSize);
}

#endif



bool IsRoutingStatusContent(struct pbuf *p) {
  return IsCmd(p, "FU");
}



static err_t OutUptime(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
  date_t days = SecondsToDate(GetClockSeconds());
  return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowClock, szUptime, days.wDays, days.bHours, days.bMinutes, days.bSeconds));
}

static err_t OutVersion(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
  timedate_t td = GetROMBuildTimeDate();
  return OutBuff(pcb,p,addr,port,broadcast,
      BuffPrintF(szRowVersion, szVersion,
          MAJOR_VERSION, MINOR_VERSION,
          GetROMBuildNumber(),
          GetROMChecksum(),
          td.bDay, td.bMonth, td.bYear, td.bHour, td.bMinute, td.bSecond
      )
  );
}

static err_t OutRemoteIP(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const char *pcszName, const ulong dw) {
  return OutBuff(pcb,p,addr,port,broadcast,
      BuffPrintF(szRowSIP, pcszName,
        (dw >> 24), (dw >> 16) & 0xFF, (dw >> 8) & 0xFF, dw & 0xFF
      )
  );
}

static err_t OutTCPError(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const char *pcszName, const uchar op, const uchar u) {
  ASSERT(op < TCP_OPERATIONS);
  ASSERT(u < UART_COUNT);

  date_t days = SecondsToDate(mdwErrTCPClockSeconds[u][op]);
  return OutBuff(pcb,p,addr,port,broadcast,
      BuffPrintF(szRowTCPError, pcszName,
          mwErrTCPErrors[u][op],
          mcwErrTCPCounters[u][op],
          days.wDays, days.bHours, days.bMinutes, days.bSeconds
      )
  );
}



static err_t GetRoutingStatusContent0(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  switch (wIdx) {
    case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
    case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);

    case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, "Runtime"));
    case 3: return OutUptime(pcb,p,addr,port,broadcast);
    case 4: return OutVersion(pcb,p,addr,port,broadcast);
    case 5: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szWatchdogReset, fWatchdogReset));

    case 6: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
    default: WARNING("routing status 0: wrong index %u\n", wIdx); return GetError();
  }
}



static err_t GetRoutingStatusContent1(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  switch (wIdx) {
    case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
    case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);

    case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, "Serial Port"));
    case 3: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, szIOMode, GetIOMode(u)));
    case 4: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mcwUARTTxOut", mcwUARTTxOut[u]));

    case 5: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, "Modem"));
    case 6: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbModemMode", mbModemMode[u]));
    case 7: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbInputMode", mbInputMode[u]));
    case 8: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbEscapeCnt", mbEscapeCnt[u]));
    case 9: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "mbEscapeMode", mbEscapeMode[u]));

    case 10: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
    default: WARNING("routing status 1: wrong index %u\n", wIdx); return GetError();
  }
}



static err_t GetRoutingStatusContent2(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  switch (wIdx) {
    case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
    case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
    case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, "TCP Events"));
    case 3: return OutTCPError(pcb,p,addr,port,broadcast,"HANDLER_ERROR",0,u);
    case 4: return OutTCPError(pcb,p,addr,port,broadcast,"HANDLER_CONNECTED",1,u);
    case 5: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_NEW_LISTEN",2,u);
    case 6: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_BIND_LISTEN",3,u);
    case 7: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_NEW_OPEN",4,u);
    case 8: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CONNECT_OPEN",5,u);
    case 9: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CONNECT_POLL",6,u);
    case 10: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CLOSE_CONNECTED",7,u);
    case 11: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CLOSE_RECEIVE",8,u);
    case 12: return OutTCPError(pcb,p,addr,port,broadcast,"TCP_CLOSE_CLOSE",9,u);
    case 13: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
    default: WARNING("routing status 2: wrong index %u\n", wIdx); return GetError();
  }
}


static err_t GetRoutingStatusContent3(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  switch (wIdx) {
    case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
    case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
    case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, "Kernel"));
    case 3: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowS08X, "pConnectPCB", g_sState[u].pConnectPCB));
    case 4: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowS08X, "pListenPCB", g_sState[u].pListenPCB));
    case 5: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "tTCPState", g_sState[u].eTCPState));
    case 6: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "usTelnetLocalPort", g_sState[u].usTelnetLocalPort));
    case 7: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "usTelnetRemotePort", g_sState[u].usTelnetRemotePort));
    case 8: return OutRemoteIP(pcb,p,addr,port,broadcast, "ulTelnetRemoteIP", g_sState[u].ulTelnetRemoteIP);
    case 9: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "ulConnectionTimeout", g_sState[u].ulConnectionTimeout));
    case 10: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "ulMaxTimeout", g_sState[u].ulMaxTimeout));
    case 11: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "ucSerialPort", g_sState[u].ucSerialPort));
    case 12: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowS08X, "pBufQ", g_sState[u].pBufQ));
    case 13: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "iBufQRead", g_sState[u].iBufQRead));
    case 14: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szRowSU, "iBufQWrite", g_sState[u].iBufQWrite));
    case 15: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
    default: WARNING("routing status 3: wrong index %u\n", wIdx); return GetError();
  }
}


static err_t GetRoutingStatusContent4(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  if (u == 0) {
    switch (wIdx) {
      case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
      case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
      case 2: return OutBuff(pcb,p,addr,port,broadcast,BuffPrintF(szHeaderS, "Error Counters"));
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
      default: WARNING("routing status 4: wrong index %u\n", wIdx); return GetError();
    }
  } else {
    switch (wIdx) {
      case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
      case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
      case 2: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
      default: WARNING("routing status 4: wrong index %u\n", wIdx); return GetError();
    }
  }
}



static err_t OutStatsMem(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, struct stats_mem *mem, const char *name) {
  return OutBuff(pcb,p,addr,port,broadcast, BuffPrintF(szMemStatsRow, name, mem->avail, mem->used, mem->max, mem->err));
}

static err_t OutStatsMemp(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, int idx) {
  struct stats_mem *mem = lwip_stats.memp[idx];
  return OutStatsMem(pcb,p,addr,port,broadcast, mem, mem->name);
}

static err_t GetRoutingStatusContent5(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast, const uint wIdx, const uchar u) {
  if (u == 0) {
    switch (wIdx) {
      case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
      case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
      case 2: return OutBuff(pcb, p, addr, port, broadcast, BuffPrintF(szMemStatsHeader));
      case 3: return OutStatsMem(pcb,p,addr,port,broadcast, &lwip_stats.mem, "HEAP");
      case 4: return OutStatsMemp(pcb,p,addr,port,broadcast, 0);
      case 5: return OutStatsMemp(pcb,p,addr,port,broadcast, 1);
      case 6: return OutStatsMemp(pcb,p,addr,port,broadcast, 2);
      case 7: return OutStatsMemp(pcb,p,addr,port,broadcast, 3);
      case 8: return OutStatsMemp(pcb,p,addr,port,broadcast, 4);
      case 9: return OutStatsMemp(pcb,p,addr,port,broadcast, 5);
      case 10: return OutStatsMemp(pcb,p,addr,port,broadcast, 6);
      case 11: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
      default: WARNING("routing status 5: wrong index %u\n", wIdx); return GetError();
    }
  } else {
    switch (wIdx) {
      case 0: return OutStringZ(pcb,p,addr,port,broadcast,szHead);
      case 1: return OutStringZ(pcb,p,addr,port,broadcast,szBodyStart);
      case 2: return OutStringZ(pcb,p,addr,port,broadcast,szBodyEnd);
      default: WARNING("routing status 5: wrong index %u\n", wIdx); return GetError();
    }
  }
}


#ifndef SINGLE_UART

err_t GetRoutingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
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

  switch (ibRoutingStatus) {
    case 0: return GetRoutingStatusContent0(pcb,p,addr,port,broadcast,wIdx,u);
    case 1: return GetRoutingStatusContent1(pcb,p,addr,port,broadcast,wIdx,u);
    case 2: return GetRoutingStatusContent2(pcb,p,addr,port,broadcast,wIdx,u);
    case 3: return GetRoutingStatusContent3(pcb,p,addr,port,broadcast,wIdx,u);
    case 4: return GetRoutingStatusContent4(pcb,p,addr,port,broadcast,wIdx,u);
    default: return GetRoutingStatusContent5(pcb,p,addr,port,broadcast,wIdx,u);
  }
}

#else

err_t GetRoutingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
  uchar2 ibStart = GetCmdEndIndex(p, "FU");
  if (InvalidChar2(ibStart)) {
    WARNING("routing status: not found 'FU'\n");
    return ibStart.err;
  }

  uint2 w2 = PopInt(p, ibStart.b, 10, '|');
  if (InvalidInt2(w2)) {
    WARNING("routing status: wrong index\n");
    return w2.err;
  }
  uint wIdx = w2.w;

//  ibStart = GetBorderIndex(p, '@');
//  if (InvalidChar2(ibStart)) {
//    WARNING("routing status: not found '@'\n");
//    return ibStart.err;
//  }
//
//  uchar2 b2 = PopCharDec(p, ibStart.b);
//  if (InvalidChar2(b2)) {
//    WARNING("routing status: wrong port\n");
//    return b2.err;
//  }
//
//  uchar bPort = b2.b;
//  if (!(bPort >= 1) && (bPort <= UART_COUNT)) {
//    WARNING("routing status: wrong port %u\n", bPort);
//    return GetError();
//  }

  uchar u = 0;
  ASSERT(u < UART_COUNT);

  switch (ibRoutingStatus) {
    case 0: return GetRoutingStatusContent0(pcb,p,addr,port,broadcast,wIdx,u);
    case 1: return GetRoutingStatusContent1(pcb,p,addr,port,broadcast,wIdx,u);
    case 2: return GetRoutingStatusContent2(pcb,p,addr,port,broadcast,wIdx,u);
    case 3: return GetRoutingStatusContent3(pcb,p,addr,port,broadcast,wIdx,u);
    case 4: return GetRoutingStatusContent4(pcb,p,addr,port,broadcast,wIdx,u);
    default: return GetRoutingStatusContent5(pcb,p,addr,port,broadcast,wIdx,u);
  }
}

#endif
