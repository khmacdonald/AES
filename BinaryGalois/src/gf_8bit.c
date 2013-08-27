#include "gf_8bit.h"
#include <stdlib.h>

/* Returns the inverse of a; returns 0 if a is zero (invalid) */
uint8_t Rijndael_Inv( uint8_t a )
{
    uint8_t power = RijndaelByValue[a];
    if ( 0==a )
        return 0;
    if ( 1==a )
        return 1;

    power = 255 - power;

    return RijndaelByPower[power];
}

/* Adds two elements in the Rijndael field */
uint8_t Rijndael_Add( uint8_t a, uint8_t b )
{
    return (a^b);
}

/* Subtracts two elements in the Rijndael field */
uint8_t Rijndael_Sub( uint8_t a, uint8_t b )
{
    return (a^b);
}

/* Multiplies two elements in the Rijndael field */
uint8_t Rijndael_Mul( uint8_t a, uint8_t b )
{
    uint8_t power = (RijndaelByValue[a] + RijndaelByValue[b]) & 0xff;
    if ( a && b )
        return RijndaelByPower[power];
    else
        return 0;
}

/* Divides two elements in the Rijndael field */
uint8_t Rijndael_Div( uint8_t a, uint8_t b )
{
    return Rijndael_Mul(a,Rijndael_Inv(b));
}