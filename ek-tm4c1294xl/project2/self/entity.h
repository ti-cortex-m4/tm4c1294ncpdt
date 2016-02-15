/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#ifndef __ENTITY_H__
#define __ENTITY_H__


typedef enum
{
  CHAR,
  INT,
  IP,
} entityType;


typedef struct
{
  ulong         dwAddr;
  void         *pbBuff;
  uint          wSize;
  uint          wMin, wMax, wDef;
  entityType    eType;
} entity;


extern const entity            enConnectionTimeout;


#endif
