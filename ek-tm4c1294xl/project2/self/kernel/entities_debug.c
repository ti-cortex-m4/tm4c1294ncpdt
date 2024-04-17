/*------------------------------------------------------------------------------
entities_debug.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
#include "entities_debug.h"



const entity enDebugMode = {
  EEPROM_DEBUG_MODE, &ibDebugMode, sizeof(uchar), CHAR, 0,
  0, 2, 0,
  "DBMD",
  "AI=DBMD;D=Debug mode;T=INT;C=STATIC;O=0-No/0/1-UDP/1/2-UART/2",
};


const entity enUDPDebugBroadcast = {
  EEPROM_UDP_DEBUG_BROADCAST, &fUDPDebugBroadcast, sizeof(uchar), CHAR, 0,
  0, 1, 1,
  "UDP_DEBUG_BROADCAST",
  "AI=UDP_DEBUG_BROADCAST;E=1;D=UDP debug broadcast;T=INT;C=STATIC;O=0-No/0/1-Yes/1;S=DBMD==1?\"e\":\"i\"",
};

const entity enUDPDebugIP = {
  EEPROM_UDP_DEBUG_IP, &dwUDPDebugIP, sizeof(ulong), IP, 0,
  0, MAX_LONG, 0xFFFFFFFF,
  "UDP_DEBUG_IP",
  "AI=UDP_DEBUG_IP;E=1;D=UDP debug IP-address;T=STRING;C=IPCTRL;S=DBMD==1&&UDP_DEBUG_BROADCAST==0?\"e\":\"i\"",
};

const entity enUDPDebugPort = {
  EEPROM_UDP_DEBUG_PORT, &wUDPDebugPort, sizeof(uint), INT, 0,
  0, MAX_INT, 50000,
  "UDP_DEBUG_PORT",
  "AI=UDP_DEBUG_PORT;E=1;D=UDP debug port;T=INT;C=EDIT;S=DBMD==1?\"e\":\"i\"",
};


const entity enLWIPDebugFlag = {
  EEPROM_LWIP_DEBUG_FLAG, &fLWIPDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "LWIPDF",
  "AI=LWIPDF;D=TCP/IP stack debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enLWIPDebugTimeout = {
  EEPROM_LWIP_DEBUG_TIMEOUT, &wLWIPDebugTimeout, sizeof(uint), INT, 0,
  0, 3600, 300,
  "LWIPDT",
  "AI=LWIPDT;E=1;D=TCP/IP stack debug period (seconds);T=INT;C=EDIT;V=LWIPDT>3600?\"Maximum timeout is 3600 seconds\":\"\";S=LWIPDF!=0?\"e\":\"i\"",
};


const entity enTCPEchoFlag = {
  EEPROM_TCP_ECHO_FLAG, &fTCPEchoFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "TCP_ECHO_FLAG",
  "AI=TCP_ECHO_FLAG;D=TCP echo;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enTCPEchoPort = {
  EEPROM_TCP_ECHO_PORT, &wTCPEchoPort, sizeof(uint), INT, 0,
  0, 65534, 7,
  "TCP_ECHO_PORT",
  "AI=TCP_ECHO_PORT;E=1;D=TCP echo port;T=INT;C=EDIT;V=TCP_ECHO_PORT>65534?\"Port number must be between 0 and 65534\":\"\";S=TCP_ECHO_FLAG!=0?\"e\":\"i\"",
};


const entity enDataDebugFlag = {
  EEPROM_DATA_DEBUG_FLAG, &fDataDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "DTDF",
  "AI=DTDF;D=Bytes debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};


const entity enIOModeDebugFlag = {
  EEPROM_IO_MODE_DEBUG_FLAG, &fIOModeDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "IOMDF",
  "AI=IOMDF;D=RS-485 I/O debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};


const entity enLED0Mode = {
  EEPROM_LED_MODE_0, &bLED0Mode, sizeof(uchar), CHAR, 0,
  0, 0, 0,
  "LED0MD",
  "AI=LED0MD;D=Ethernet LED0 mode;T=INT;C=STATIC;O=0-Link OK/0",
};

const entity enLED1Mode = {
  EEPROM_LED_MODE_1, &bLED1Mode, sizeof(uchar), CHAR, 0,
  0, 8, 1,
  "LED1MD",
  "AI=LED1MD;D=Ethernet LED1 mode;T=INT;C=STATIC;O=0-Link OK/0/1-RX\\TX activity/1/2-TX activity/2/3-RX activity/3/4-Collision/4/5-100-Base TX speed/5/6-10-Base TX speed/6/7-Full duplex/7/8-Link OK, blink on TX\\RX activity/8",
};


const entity enPowerUpResetCount = {
  EEPROM_POWER_UP_RESET_COUNT, &cwPowerUpResetCount, sizeof(uint), INT, 0,
  0, 0xFFFE, 0,
  "",
  "",
};

const entity enWatchdogResetCount = {
  EEPROM_WATCHDOG_RESET_COUNT, &cwWatchdogResetCount, sizeof(uint), INT, 0,
  0, 0xFFFE, 0,
  "",
  "",
};

const entity enLinkUpResetCount = {
  EEPROM_LINK_UP_RESET_COUNT, &cwLinkUpResetCount, sizeof(uint), INT, 0,
  0, 0xFFFE, 0,
  "",
  "",
};


const entity enPeriodicResetFlag = {
  EEPROM_PERIODIC_RESET_FLAG, &fPeriodicResetFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "PERIODIC_RESET_FLAG",
  "AI=PERIODIC_RESET_FLAG;D=Periodic reset;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enPeriodicResetPeriod = {
  EEPROM_PERIODIC_RESET_PERIOD, &wPeriodicResetPeriod, sizeof(uint), INT, 0,
  1, 24, 24,
  "PERIODIC_RESET_PERIOD",
  "AI=PERIODIC_RESET_PERIOD;E=1;D=Periodic reset period (minutes);T=INT;C=EDIT;V=PERIODIC_RESET_PERIOD<1||PERIODIC_RESET_PERIOD>1440?\"Periodic reset period must be between 1 and 1440 minutes\":\"\";S=PERIODIC_RESET_FLAG==1?\"e\":\"i\"",
};


const entity enLinkUpResetFlag = {
  EEPROM_LINK_UP_RESET_FLAG, &fLinkUpResetFlag, sizeof(uchar), CHAR, 0,
  0, 1, 1,
  "LINK_UP_RESET_FLAG",
  "AI=LINK_UP_RESET_FLAG;D=Link up reset;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enLinkUpResetTimeout = {
  EEPROM_LINK_UP_RESET_TIMEOUT, &wLinkUpResetTimeout, sizeof(uint), INT, 0,
  1, 60, 5,
  "LINK_UP_RESET_TIMEOUT",
  "AI=LINK_UP_RESET_TIMEOUT;E=1;D=Link up reset timeout (seconds);T=INT;C=EDIT;V=LINK_UP_RESET_TIMEOUT<1||LINK_UP_RESET_TIMEOUT>60?\"Link up reset timeout must be between 1 and 60 seconds\":\"\";S=LINK_UP_RESET_FLAG==1?\"e\":\"i\"",
};

const entity enLinkUpResetMode = {
  EEPROM_LINK_UP_RESET_MODE, &fLinkUpResetMode, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "LINK_UP_RESET_MODE",
  "AI=LINK_UP_RESET_MODE;E=1;D=Link up reset mode;T=INT;C=STATIC;O=0-Software reset/0/1-Hardware reset/1;S=LINK_UP_RESET_FLAG==1?\"e\":\"i\"",
};
