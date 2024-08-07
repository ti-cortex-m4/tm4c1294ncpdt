/*------------------------------------------------------------------------------
devices_include.h


------------------------------------------------------------------------------*/

#ifndef __DEVICES_INCLUDE
#define __DEVICES_INCLUDE


#define CURRENT_REPEAT_OR_ERROR(method, action) { if (cbRepeat == 0) ErrorCurrent(); else { ErrorLink(); cbRepeat--; method; SetCurr(action); } }

#define PROFILE_REPEAT_OR_ERROR(method, action) { if (cbRepeat == 0) ErrorProfile(); else { ErrorLink(); cbRepeat--; method; SetCurr(action); } }


#endif
