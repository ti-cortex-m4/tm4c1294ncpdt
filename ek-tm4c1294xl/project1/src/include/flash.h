/*------------------------------------------------------------------------------
FLASH.H

 Ќастройки флэш-пам€ти
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH


// размер страницы
#define wPAGE_SIZE      528

// размер страницы, доступный дл€ записи данных пользовател€
#define wFREEPAGE_SIZE  512

// количество страниц
#define wPAGES          8192


// количество повторов при чтении регистра состо€ни€
#define wREAD_STATUS    50000

// количество повторов при чтени€/записи страницы
#define bMAXREPEAT      8


// адреса блоков данных
#define wFLA_BEGIN      0

#define wFLA_PRIVATE    (uint)(wFLA_BEGIN)
#define wFLA_GLOBAL     (uint)(wFLA_PRIVATE + 1)
#define wFLA_LOGICAL    (uint)(wFLA_GLOBAL + 1)

#define wFLA_GROUPS     (uint)(wFLA_LOGICAL + 1)

#define wFLA_TRANS_ENG  (uint)(wFLA_GROUPS + sizeof(group)*bGROUPS/wFREEPAGE_SIZE + 1)
#define wFLA_TRANS_CNT  (uint)(wFLA_TRANS_ENG + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)
#define wFLA_PULSE_HOU  (uint)(wFLA_TRANS_CNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)
#define wFLA_PULSE_MNT  (uint)(wFLA_PULSE_HOU + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)

#define wFLA_COUNT      (uint)(wFLA_PULSE_MNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)
#define wFLA_LOSSE      (uint)(wFLA_COUNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)
#define wFLA_LEVEL      (uint)(wFLA_LOSSE + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)

#define wFLA_END        (uint)(wFLA_LEVEL + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1)


#endif
