#include "gf_8bit.h"
#include <stdlib.h>

/* Returns the inverse of a; returns 0 if a is zero (invalid) */
uint8_t Rijndael_Inv( uint8_t a )
{
    uint8_t power = RijndaelByValue[a];
    if ( 0==a )
        return 0; /* Does not have a multiplicative inverse */
    if ( 1==a )
        return 1; /* 1 is it's own inverse */

    power = 255 - power; /* ab=1 where a=g^i and b=g^(255-i) */

    return RijndaelByPower[power];
}

/* Adds two elements in the Rijndael field */
uint8_t Rijndael_Add( uint8_t a, uint8_t b )
{
    return (a^b); /* Addition is GF(256) is bit-wise XOR */
}

/* Subtracts two elements in the Rijndael field */
uint8_t Rijndael_Sub( uint8_t a, uint8_t b )
{
    return (a^b); /* Subtraction is addition in binary fields */
}

/* Multiplies two elements in the Rijndael field */
uint8_t Rijndael_Mul( uint8_t a, uint8_t b )
{
    uint8_t power = (RijndaelByValue[a] + RijndaelByValue[b]) & 0xff;

    /* 
     * ab = c, where a=g^i and b=g^j, then c=g^(i+j) 
     * The addition i+j is computed mod 256 since g^256=1
     */
    if ( a && b )
        return RijndaelByPower[power];
    else
        return 0;
}

/* Divides two elements in the Rijndael field */
uint8_t Rijndael_Div( uint8_t a, uint8_t b )
{
    /* a/b = ab^(-1) */
    return Rijndael_Mul(a,Rijndael_Inv(b));
}
