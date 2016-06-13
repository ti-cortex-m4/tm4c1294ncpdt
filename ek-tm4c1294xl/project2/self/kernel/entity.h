/*------------------------------------------------------------------------------
entity.h


------------------------------------------------------------------------------*/

#ifndef __ENTITY_H__
#define __ENTITY_H__


typedef enum
{
  CHAR,
  INT,
  IP,
  STRING,
} entityType;


typedef enum
{
  FLAG_DONT_RESET = 1,
} entityFlags;


typedef struct
{
  ulong         dwEepRom;
  void         *pbRam;
  uint          wSize;
  entityType    eType;
  ulong         dwFlags;
  ulong         dwMin, dwMax, dwDef;
  message       szCode;
  message       szName;
} entity;


#endif


ulong SaveEntity(const entity * const pen);
void LoadEntity(const entity * const pen);
void LoadEntityDef(const entity * const pen);
