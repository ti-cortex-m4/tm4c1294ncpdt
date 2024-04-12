/*------------------------------------------------------------------------------
link_up_reset.h


------------------------------------------------------------------------------*/

#ifndef __LINK_UP_RESET_H__
#define __LINK_UP_RESET_H__


typedef enum
{
  LUR_LINK_UNKNOWN = 0,
  LUR_LINK_UP = 1,
  LUR_LINK_DOWN = 2,
} lur_t;



void InitLinkUpReset(void);
void LinkUpReset_LinkUp(void);
void LinkUpReset_LinkDown(void);
void LinkUpReset_1Hz(void);
void RunLinkUpReset(void);


#endif
