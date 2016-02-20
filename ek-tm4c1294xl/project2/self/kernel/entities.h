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
  STRING,
} entityType;


typedef struct
{
  ulong         dwEepRom;
  void         *pbRam;
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


#include "entities_general.h"
#include "entities_channels.h"


extern const entity * const mpenEntities[];
extern const uchar bEntitiesSize;


extern const entity enSerialNumber;

extern const entity enDebugMode;

extern const entity enUdpDebugIP;
extern const entity enUdpDebugPort;

extern const entity enLwIpDebugFlag;
extern const entity enLwIpDebugTimeout;
