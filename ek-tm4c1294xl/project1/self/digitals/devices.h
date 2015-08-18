/*------------------------------------------------------------------------------
DEVICES.H
              

------------------------------------------------------------------------------*/

extern  message                 mpszDevices[bMAXDEVICES+1];
extern  uchar const             mpbMaxLines[bMAXDEVICES+1];



bool    IsValidDevice(uchar  ibDevice);
void    ShowDeviceName(uchar  ibDevice);
