/*------------------------------------------------------------------------------
entities.h


------------------------------------------------------------------------------*/

#ifndef __ENTITIES_H__
#define __ENTITIES_H__


typedef enum
{
  CHAR,
  INT,
  IP,
} entityType;


typedef struct
{
  ulong         dwEEPROM;
  void         *pbRAM;
  uint          wSize;
  entityType    eType;
  ulong         dwMin, dwMax, dwDef;
  const char    *szCode, *szName;
} entity;


typedef enum
{
  ROUTING_MODE_SERVER = 0,
  ROUTING_MODE_CLIENT = 1,
} routingMode;


typedef enum
{
  CONNECTION_MODE_IMMEDIATELY = 0,
  CONNECTION_MODE_ON_DATA = 1,
} connectionMode;


typedef enum
{
  DEBUG_MODE_NONE = 0,
  DEBUG_MODE_UDP = 1,
  DEBUG_MODE_UART = 2,
} debugMode;


#endif


extern const entity enConnectionTimeout0;
extern const entity enConnectionTimeout1;
extern const entity enConnectionTimeout2;

extern const entity enRoutingMode0;
extern const entity enRoutingMode1;
extern const entity enRoutingMode2;

extern const entity enPort0;
extern const entity enPort1;
extern const entity enPort2;

extern const entity enConnectionMode0;
extern const entity enConnectionMode1;
extern const entity enConnectionMode2;

extern const entity enDestinationIP0;
extern const entity enDestinationIP1;
extern const entity enDestinationIP2;

extern const entity enDestinationPort0;
extern const entity enDestinationPort1;
extern const entity enDestinationPort2;

extern const entity enBaudRate0;
extern const entity enBaudRate1;
extern const entity enBaudRate2;

extern const entity enSerialNumber;

extern const entity enDebugMode;

extern const entity enUdpDebugIP;
extern const entity enUdpDebugPort;

extern const entity enLwIpDebugFlag;
extern const entity enLwIpDebugTimeout;
