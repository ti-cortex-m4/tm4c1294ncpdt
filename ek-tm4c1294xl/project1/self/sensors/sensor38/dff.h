/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

uchar   DffEncode(int64_t  value, uchar  *pbOut);
int     EncodeInt(int64_t  value, uchar  *pbOut);

uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut);
uchar*  DffDecodePositive(uchar  *pbIn, int64_t  *pdwOut);
