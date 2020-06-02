/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

uchar   EncodeInt(uchar*  send_buffer_position, int64_t  value);

uint64_t    DffPopDecodeLong64(uchar  i);

uint64_t    DffDecodeLong64(uchar  *pb);
ulong       DffDecodeLong(uchar  *pb);

uchar*  DffDecodeLong64_(uchar  *pb, int64_t  *pOut);
