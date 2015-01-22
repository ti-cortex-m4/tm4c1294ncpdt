/*------------------------------------------------------------------------------
FLASH.H

 Ќастройки флэш-пам€ти
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH


// размер страницы
#define wPAGE_SIZE      1056

// размер страницы, доступный дл€ записи данных пользовател€
#define wFREEPAGE_SIZE  1040

// количество страниц
#define wPAGES          8192


// количество повторов при чтении регистра состо€ни€
#define wMAXBUSY        1000

// количество повторов при чтени€/записи страницы
#define bMAXREPEAT      8


// адреса блоков данных
#define wFLA_BEGIN      0
#define wFLA_PRIVATE    (uint)(wFLA_BEGIN)
#define wFLA_LABEL      (uint)(wFLA_PRIVATE   + 1)
#define wFLA_END        (uint)(wFLA_LABEL     + 1)


#endif
