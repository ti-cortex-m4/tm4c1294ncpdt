/*------------------------------------------------------------------------------
crypto34.h


------------------------------------------------------------------------------*/

void    HashMD5(const uchar *in, size_t size, uchar *out);
void    EncryptAES(const uchar *userKey, const uchar *in, uchar *out);
