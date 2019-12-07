/*------------------------------------------------------------------------------
auto_transit.h


------------------------------------------------------------------------------*/

#ifndef __AUTO_TRANSIT
#define __AUTO_TRANSIT


typedef struct
{
  uchar         bMinuteStart;
  uchar         bMinuteStop;
  bool          fEnabled;
} auto_transit;


#endif



extern  auto_transit            stAutoTransit;
extern  cache const             chAutoTransit;
