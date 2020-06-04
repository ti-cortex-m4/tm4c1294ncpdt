/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

uchar   EncodeInt_(uchar*  send_buffer_position, int64_t  value);

int EncodeInt(int64_t value, uint8_t *send_buffer_position);

uint64_t    DffDecodeLong64(uchar  *pb);

uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut);

unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn);
