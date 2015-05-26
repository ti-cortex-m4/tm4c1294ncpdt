/*------------------------------------------------------------------------------
MAIN_EXTENDED.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_EXTENDED
#define __MAIN_EXTENDED


// тип 'статус опроса цифровых счетчиков'
typedef enum
{
  ST4_NONE              = 0,
  ST4_OK                = 1,
  ST4_NOTSUPPORTED      = 2,
  ST4_NOTPRESENTED      = 3,
  ST4_BADDIGITAL        = 0x80,
  ST4_BADFLASH          = 0x81,
  ST4_BADPORT           = 0x82,
  ST4_BADENABLING       = 0x83
} status;


// тип 'данные типа 4'
typedef struct
{
  status        bSelf;
  uint          cwOK,cwError;
  real          reSelf;
  time          tiSelf;
} value4;


// тип 'буфер типа 5'
typedef struct
{
  double        mpdbValuesT[bTARIFFS];
} value5a;


// тип 'данные типа 5'
typedef struct
{
  value5a       stValue;
  time          tiUpdate;
  boolean       boSuccess;
  uint          cwSuccess,cwError;
} value5b;


// тип 'данные типа 6'
typedef struct
{
  status        bStatus;
  double        dbValue;
  time          tiUpdate;
} value6;


// тип 'данные типа 6 по тарифам'
typedef struct
{
  status        bStatus;
  double        mpdbValuesT[bTARIFFS];
  time          tiUpdate;
} value4t;


// тип 'данные типа 7'
typedef struct
{
  uchar         bSelf;
  uint          mpwSelf[4];
  time          tiSelf;
} value7;


// тип 'диаграмма'
typedef struct
{
  real          dbValue;
  time2         tmSelf;
} diagram;


// константы
#define bVALUE7_BLOCKS      3
#define bVALUE7_USED_SIZE   (bVALUE7_BLOCKS*6) 
#define bVALUE7_REAL_SIZE   ((bVALUE7_BLOCKS+1)*6) 


#endif
