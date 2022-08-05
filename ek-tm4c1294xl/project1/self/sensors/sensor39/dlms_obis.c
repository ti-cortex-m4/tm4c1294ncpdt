/*------------------------------------------------------------------------------
dlms_obis.c

Blue Book: 7.5.1 Value group C codes – Electricity
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "dlms_obis.h"



const obis_t        obisId      = {0, 0, 96, 1, 0, 255}; // Ch. 0; Device ID 1, manufacturing number

const obis_t        obisTime    = {0, 0, 1, 0, 0, 255}; // Ch. 0; Clock object; #1

const obis_t        obisEngAbs[4] = {
  {1, 0, 1, 8, 0, 255}, // Ch. 0; Sum Li Active power+   (QI+QIV);   Time integral 1; Rate 0 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 2, 8, 0, 255}, // Ch. 0; Sum Li Active power-   (QII+QIII); Time integral 1; Rate 0 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 3, 8, 0, 255}, // Ch. 0; Sum Li Reactive power+ (QI+QII);   Time integral 1; Rate 0 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 4, 8, 0, 255}, // Ch. 0; Sum Li Reactive power- (QIII+QIV); Time integral 1; Rate 0 (0 is total); Unspecified number of most recent billing periods
};

const obis_t        obisEngAbsTariff[4] = {
  {1, 0, 15, 8, 1, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 1 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 15, 8, 2, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 2 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 15, 8, 3, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 3 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 15, 8, 4, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 4 (0 is total); Unspecified number of most recent billing periods
};

const obis_t        obisBillingPeriod = {0, 0, 98, 1, 0, 255}; // Ch. 0; Data of billing period; Scheme 1; #1; Unspecified number of most recent billing periods

const obis_t        obisProfile = {1, 0, 99, 1, 0, 255}; // Ch. 0; Load profile with recording period 1; #1

const obis_t        obisU1      = {1, 0, 32, 7, 0, 255}; // Ch. 0; L1 Voltage; Inst. value
const obis_t        obisU2      = {1, 0, 52, 7, 0, 255}; // Ch. 0; L2 Voltage; Inst. value
const obis_t        obisU3      = {1, 0, 72, 7, 0, 255}; // Ch. 0; L3 Voltage; Inst. value

const obis_t        obisI1      = {1, 0, 31, 7, 0, 255}; // Ch. 0; L1 Current ; Inst. value
const obis_t        obisI2      = {1, 0, 51, 7, 0, 255}; // Ch. 0; L2 Current ; Inst. value
const obis_t        obisI3      = {1, 0, 71, 7, 0, 255}; // Ch. 0; L3 Current ; Inst. value

const obis_t        obisP       = {1, 0,  1, 7, 0, 255}; // Ch. 0; Sum Li Active power+ (QI+QIV); Inst. value
const obis_t        obisP1      = {1, 0, 21, 7, 0, 255}; // Ch. 0; L1 Active power+ (QI+QIV); Inst. value
const obis_t        obisP2      = {1, 0, 41, 7, 0, 255}; // Ch. 0; L2 Active power+ (QI+QIV); Inst. value
const obis_t        obisP3      = {1, 0, 61, 7, 0, 255}; // Ch. 0; L3 Active power+ (QI+QIV); Inst. value

const obis_t        obisQ       = {1, 0,  3, 7, 0, 255}; // Ch. 0; Sum Li Reactive power+ (QI+QII); Inst. value
const obis_t        obisQ1      = {1, 0, 23, 7, 0, 255}; // Ch. 0; L1 Reactive power+ (QI+QII); Inst. value
const obis_t        obisQ2      = {1, 0, 43, 7, 0, 255}; // Ch. 0; L2 Reactive power+ (QI+QII); Inst. value
const obis_t        obisQ3      = {1, 0, 63, 7, 0, 255}; // Ch. 0; L3 Reactive power+ (QI+QII); Inst. value

const obis_t        obisS       = {1, 0,  9, 7, 0, 255}; // Ch. 0; Sum Li Apparent power+ (QI+QIV); Inst. value
const obis_t        obisS1      = {1, 0, 29, 7, 0, 255}; // Ch. 0; L1 Apparent power+ (QI+QIV); Inst. value
const obis_t        obisS2      = {1, 0, 49, 7, 0, 255}; // Ch. 0; L2 Apparent power+ (QI+QIV); Inst. value
const obis_t        obisS3      = {1, 0, 69, 7, 0, 255}; // Ch. 0; L3 Apparent power+ (QI+QIV); Inst. value

const obis_t        obisF       = {1, 0, 14, 7, 0, 255}; // Ch. 0; Supply frequency; Inst. value
