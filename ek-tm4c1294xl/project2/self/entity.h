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
  uint          wMin, wMax, wDef;
  const char    *szCode, *szName;
} entity;


extern const entity enConnectionTimeout;


#endif
