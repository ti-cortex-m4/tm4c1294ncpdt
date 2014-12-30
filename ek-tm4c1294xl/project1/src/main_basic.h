#ifndef __MAIN_BASIC
#define __MAIN_BASIC


typedef unsigned char   uchar;
typedef signed char     schar;

typedef unsigned int    uint;
typedef signed int      sint;

typedef unsigned long   ulong;
typedef signed long     slong;


// тип 'время и дата'
typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
  uchar         bDay;
  uchar         bMonth;
  uchar         bYear;
} time;


typedef enum
{
  boFalse               = 0x00,
  boTrue                = 0xFF
} boolean;


#endif
