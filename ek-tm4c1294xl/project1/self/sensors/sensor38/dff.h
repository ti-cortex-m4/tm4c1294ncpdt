/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

uchar   DffEncode(int64_t  value, uchar*  send_buffer_position);

int EncodeInt(int64_t value, uint8_t *send_buffer_position);

uint64_t    DffDecodeLong64(uchar  *pb);

uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut);

unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn);
