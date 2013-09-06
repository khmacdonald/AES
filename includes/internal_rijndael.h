#ifndef INTERNAL_AES_H
#define INTERNAL_AES_H

#include "rijndael.h"

#define STATELEN   16
#define MAXKEY  32
#define MAXRND  14
#define MXEKEY  MAXKEY*MAXRND
#define NUM_COL 4

/* Adds the round key to state */
void AddRoundKey( void );

/* Transforms the cipher by mixing the columns */
void MixColumns( void );

/* Permutes a four byte word */
uint32_t RotWord( uint32_t w);

/* Transforms the cipher by cyclically permuting rows */
void ShiftRows( void );

/* Performs byte s-box operation */
void SubBytes( void );

/* Performs a four byte s-box operation */
uint32_t SubWord( uint32_t w );

/* The inverse of MixColumns */
void InvMixColumns( void );

/* The inverse of ShiftRows */
void InvShiftRows( void );

/* The inverse of SubBytes*/
void InvSubBytes( void );

/* Expands the key for all encryption rounds */
void KeyExpansion( uint8_t * key, uint32_t * w);

#endif
