/*------------------------------------------------------------------------------
md5.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../../openssl/include/openssl/md5.h"



unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md)
{
  MD5_CTX c;
  MD5_Init(&c);
  MD5_Update(&c, d, n);
  MD5_Final(md, &c);
  return md;
}


void    RunMD5(void) {
  const unsigned char* string = "111111";
  unsigned char digest[16];
  MD5(string, 6, digest);
}



