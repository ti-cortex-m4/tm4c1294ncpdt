/*------------------------------------------------------------------------------
phones2_include*h


------------------------------------------------------------------------------*/

#ifndef __PHONES2_INCLUDE
#define __PHONES2_INCLUDE


// количество кодов результата СМС-контроля
#define PHONE2_CODES      10

// размер буфера результата СМС-контроля
#define PHONE2_ANSWER     50

// размер буфера журнала СМС-контроля
#define PHONE2_RECORD     8


typedef enum
{
  PH2_OK                = 1,
  PH2_KEYBREAK          = 2,
  PH2_MODEMCOMMON       = 3,
  PH2_MESSAGEMODE       = 4,
  PH2_MESSAGE1          = 5,
  PH2_MESSAGE2          = 6
} phones2;


typedef struct
{
  uint          cwSelf;
  time          tiSelf;
} stamp2;


#endif
