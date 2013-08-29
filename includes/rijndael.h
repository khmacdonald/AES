#ifndef AES_H
#define AES_H

#define STLEN   16
#define MAXKEY  32
#define MAXRND  14
#define MXEKEY  MAXKEY*MAXRND

#define SUCCESS 0
#define FAILURE 1
#define NOMEM   2
#define INVARG  3

typedef unsigned char uchar;
typedef unsigned int  uint;

/**
 * This encrypts the 128 bit vector in and puts the encrypted 128 bit vector
 * in out.  This function is safe to have in and out be the array.  
 *
 * out - The encrypted vector.  It is assumed to be 16 bytes long.
 * in  - The vector to be encrypted.  It is assumed to be 16 bytes long.
 * key - The encryption key to be used.
 * keylen - The length of the key.  It can only be 16, 24, or 32.
 */
int rijndael_encrypt( uchar * out, uchar * in, uchar * key, int keylen );

/**
 * This decrypts the 128 bit vector in and puts the encrypted 128 bit vector
 * in out.  This function is safe to have in and out be the array.  
 *
 * out - The decrypted vector.  It is assumed to be 16 bytes long.
 * in  - The vector to be decrypted.  It is assumed to be 16 bytes long.
 * key - The encryption key to be used.
 * keylen - The length of the key.  It can only be 16, 24, or 32.
 */
int rijndael_decrypt( uchar * out, uchar * in, uchar * key, int keylen );

#endif
