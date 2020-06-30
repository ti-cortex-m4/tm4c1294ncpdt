/*------------------------------------------------------------------------------
devices_include.h


------------------------------------------------------------------------------*/

#ifndef __DEVICES_INCLUDE
#define __DEVICES_INCLUDE


#define PROFILE_REPEAT_OR_ERROR(method, action) { if (cbRepeat == 0) ErrorProfile(); else { ErrorLink(); cbRepeat--; QueryTime38(); SetCurr(DEV_TIME1_38P); } }


#endif
