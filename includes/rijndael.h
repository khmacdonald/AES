#ifndef AES_H
#define AES_H

#include <stdint.h>

#define KEY_128  16
#define KEY_192  24
#define KEY_256  32

#define SUCCESS 0
#define FAILURE 1
#define NOMEM   2
#define INVARG  3

/**
 * This encrypts the 128 bit vector in and puts the encrypted 128 bit vector
 * in out.  This function is safe to have in and out be the array.  
 *
 * out - The encrypted vector.  It is assumed to be 16 bytes long.
 * in  - The vector to be encrypted.  It is assumed to be 16 bytes long.
 * key - The encryption key to be used.
 * keylen - The length of the key.  It can only be 16, 24, or 32.
 */
int32_t rijndael_encrypt( uint8_t * out, uint8_t * in, uint8_t * key, int32_t keylen );

/**
 * This decrypts the 128 bit vector in and puts the encrypted 128 bit vector
 * in out.  This function is safe to have in and out be the array.  
 *
 * out - The decrypted vector.  It is assumed to be 16 bytes long.
 * in  - The vector to be decrypted.  It is assumed to be 16 bytes long.
 * key - The encryption key to be used.
 * keylen - The length of the key.  It can only be 16, 24, or 32.
 */
int32_t rijndael_decrypt( uint8_t * out, uint8_t * in, uint8_t * key, int32_t keylen );

#endif
