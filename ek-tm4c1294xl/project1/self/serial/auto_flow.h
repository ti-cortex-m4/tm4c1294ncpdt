/*------------------------------------------------------------------------------
auto_transit.h


------------------------------------------------------------------------------*/

#ifndef __AUTO_TRANSIT
#define __AUTO_TRANSIT


typedef struct
{
  bool          fEnabled;
  uchar         bMinuteStart;
  uchar         bMinuteStop;
} auto_transit;


#endif



extern  auto_transit            stAutoTransit;
extern  cache const             chAutoTransit;



void    InitAutoTransit(void);
void    ResetAutoFlow(void);
