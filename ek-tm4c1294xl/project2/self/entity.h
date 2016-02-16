/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#ifndef __ENTITY_H__
#define __ENTITY_H__


typedef enum
{
  CHAR,
  INT,
  LONG,
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


extern const entity enConnectionTimeout;
extern const entity enRoutingMode;
extern const entity enDestIP;
extern const entity enDestPort;

extern const entity enBaudRate0;
extern const entity enBaudRate1;

extern const entity enUdpDebugFlag;
extern const entity enUdpDebugPort;


#endif
