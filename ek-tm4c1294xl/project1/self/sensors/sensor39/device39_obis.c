/*------------------------------------------------------------------------------
device39_obis.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "device39_obis.h"



const obis_t        obisId      = {0, 0, 96, 1, 4, 255};

const obis_t        obisTime    = {0, 0, 1, 0, 0, 255};

const obis_t        obisEngAbs  = {1, 0, 15, 8, 0, 255}; // Ch. 0 Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)) Time integral 1 Rate 0 (0 is total)

const obis_t        obisEngAbsTariff[4] = {
  {1, 0, 15, 8, 1, 255},                                 // Ch. 0 Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)) Time integral 1 Rate 1 (0 is total)
  {1, 0, 15, 8, 2, 255},
  {1, 0, 15, 8, 3, 255},
  {1, 0, 15, 8, 4, 255},
};

const obis_t        obisBillingPeriod = {0, 0, 98, 1, 0, 255};

const obis_t        obisProfile  = {1, 0, 99, 1, 0, 255};
