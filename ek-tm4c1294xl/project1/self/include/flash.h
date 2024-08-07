/*------------------------------------------------------------------------------
FLASH!H

 ��������� ����-������
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH

#include "../memory/mem_extended_4.h"
#include "../memory/mem_extended_4t.h"
#include "../memory/mem_extended_5.h"
#include "../memory/mem_extended_6.h"
#include "../memory/mem_extended_7.h"
#include "../memory/mem_diagram.h"
#include "../memory/mem_correct1.h"



// ������ ��������
#define wPAGE_BYTES     528

// ������ ��������, ��������� ��� ������ ������ ������������
#define wLEAF_BYTES     512

// ���������� ������� �� ���� ����������
#define wPAGES          8192

// ���������� �������
#ifdef NO_DISPLAY
#define wPAGES_TOTAL    (wPAGES*1)
#else
#define wPAGES_TOTAL    (wPAGES*2)
#endif

// ���������� �������� ��� ������ �������� ��������� (TODO: use milliseconds)
#define STATUS_REPEATS  50000


// ���������� ������� �� ���� ������
#define UINT_CAN_PAGES      (uchar)(sizeof(uint)    * bCANALS/wLEAF_BYTES + 1)
#define IMP_CAN_PAGES       (uchar)(sizeof(impulse) * bCANALS/wLEAF_BYTES + 1)
#define MAXPOW_GRP_PAGES    (uchar)(sizeof(power)   * bGROUPS/wLEAF_BYTES + 1)
#define FLOAT_CAN_PAGES     (uchar)(sizeof(float)   * bCANALS/wLEAF_BYTES + 1)
#define DOUBLE_CAN_PAGES    (uchar)(sizeof(double)  * bCANALS/wLEAF_BYTES + 1)
#define PARAMS_PAGES        (uchar)(sizeof(float)   * wPARAMS/wLEAF_BYTES + 1)
#define VALUE4_CAN_PAGES    (uchar)(sizeof(mpCntMonCan4)/wLEAF_BYTES + 1)
#define VALUE4T_CAN_PAGES   (uchar)(sizeof(mpCntMonCan4T)/wLEAF_BYTES + 1)
#define VALUE5_CAN_PAGES    (uchar)(sizeof(mpCntDayCan5)/wLEAF_BYTES + 1)
#define VALUE6_CAN_PAGES    (uchar)(sizeof(mpCntMonCan6)/wLEAF_BYTES + 1)
#define VALUE7_CAN_PAGES    (uchar)(sizeof(mpCntDayCan7)/wLEAF_BYTES + 1)

#define DIAGRAM_CAN_PAGES   (uchar)(sizeof(mpDiagram)/wLEAF_BYTES + 1)
#define DIAGRAM_PAGES       (uint)(wHOURS_DIAGRAM*DIAGRAM_CAN_PAGES)


// ������ ����� ������
#define SIZEOF_RECORD   (uchar)(6+4+1+8)

// ���������� ������ ������ �� ��������
#define bRECORD_BLOCK   (uchar)(wLEAF_BYTES/SIZEOF_RECORD)

// ���������� ������� �� ������ �������
#define bRECORD_PAGES   (uchar)(wRECORDS/bRECORD_BLOCK + 1)
#define wRECORD2_PAGES  (uint)(wRECORDS2/bRECORD_BLOCK + 1)


// ���������� ������� ��� ������� �������� �� ���������
#ifdef  DAYS100

#define IMPHOUCAN_PAGES     (uint)(wHOURS/4)

#else

#define IMPHOUCAN_PAGES     (uint)(wHOURS/1)

#endif


#ifdef NO_DISPLAY
#include "../generated/flash_enum.no_display.txt"
#else
#include "../generated/flash_enum.txt"
#endif


#if (LOCAL_END >= wPAGES)
#error "FLASH1 pages layout overflow"
#endif

#if (FLASH_END >= wPAGES_TOTAL)
#error "FLASH2 pages layout overflow"
#endif

#endif
