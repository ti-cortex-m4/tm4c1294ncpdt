/*------------------------------------------------------------------------------
device39_obis.h


------------------------------------------------------------------------------*/

#ifndef __DEVICE39_OBIS
#define __DEVICE39_OBIS


typedef uchar           obis_t[6];


#endif


extern  const obis_t        obisId;

extern  const obis_t        obisTime;

extern  const obis_t        obisEngAbs;

extern  const obis_t        obisEngAbsTariff[4];

extern  const obis_t        obisBillingPeriod;

extern  const obis_t        obisProfile;

extern  const obis_t        obisU1,
                            obisU2,
                            obisU3,

                            obisI1,
                            obisI2,
                            obisI3,

                            obisPplus,
                            obisPminus,

                            obisQplus,
                            obisQminus;
