#ifndef GF_8BIT_H
#define GF_8BIT_H

#include <stdio.h>
#include <stdint.h>

/*
 * The driver polynomial is x^8+x^4+x^3+x+1, which corresponds to 100011011 in binary, 
 * which further corresponds to 0x11b.  This means that in the field 0x100=0x1b.
 */
#define RIJNDAEL     0x1b

//typedef unsigned char uint8_t;
//typedef          int   int32_t;

/* Error return codes */
#define SUCCESS        0
#define BADARGS        1

extern uint8_t RijndaelByValue[256];
extern uint8_t RijndaelByPower[256];

uint8_t Rijndael_Inv( uint8_t a );
uint8_t Rijndael_Add( uint8_t a, uint8_t b );
uint8_t Rijndael_Sub( uint8_t a, uint8_t b );
uint8_t Rijndael_Mul( uint8_t a, uint8_t b );
uint8_t Rijndael_Div( uint8_t a, uint8_t b );

#endif
