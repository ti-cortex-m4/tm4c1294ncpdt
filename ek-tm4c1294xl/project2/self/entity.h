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


extern const entity enConnectionTimeout0;
extern const entity enConnectionTimeout1;

extern const entity enRoutingMode0;
extern const entity enRoutingMode1;

extern const entity enPort0;
extern const entity enPort1;

extern const entity enDestinationIP0;
extern const entity enDestinationIP1;

extern const entity enDestinationPort0;
extern const entity enDestinationPort1;

extern const entity enBaudRate0;
extern const entity enBaudRate1;

extern const entity enUdpDebugFlag;
extern const entity enUdpDebugPort;


#endif
