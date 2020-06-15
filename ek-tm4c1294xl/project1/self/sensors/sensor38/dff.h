/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

uchar   DffEncode(int64_t  ddwValue, uchar  *pbOut);
int     Encode38(int64_t  ddwValue, uchar  *pbOut);

uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut);
uchar*  DffDecodePositive(uchar  *pbIn, int64_t  *pdwOut);
