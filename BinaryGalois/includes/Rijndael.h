#ifndef RIJNDAEL_H
#define RIJNDAEL_H

#include "gf_8bit.h"

#define MAXROUNDS          14
#define NUM_COL             4

#define AES_BLOCK_SIZE      16
#define AES_MAX_KEY_SIZE   240 /* 128*(14+1)/8 */

#define AES_128        16
#define AES_192        24
#define AES_256        32

/* Expands the key into ekey based on the parameters Nk and Nr. */
void KeyExpansion( uint8_t eKey[AES_MAX_KEY_SIZE], uint8_t key[AES_256], int32_t Nk, int32_t Nr );

/* Encrypts a 128 bit block, called state using the expanded key and the parameter Nr */
void RijndaelEncrypt( uint8_t state[AES_BLOCK_SIZE], uint8_t eKey[AES_MAX_KEY_SIZE],int32_t Nr );

/* Tests the encryption against a known vector */
void TestEncrypt( void );

#endif
