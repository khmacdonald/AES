#include "Rijndael.h"

uint8_t s_box[256] = 
{
   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

uint8_t inv_s_box[256] = 
{
   0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
   0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
   0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
   0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
   0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
   0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
   0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
   0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
   0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
   0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
   0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
   0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
   0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
   0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
   0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
   0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

/* ----------------------------------------------- */
/* ---------------- Key Schedule ----------------- */
/*                                                 */

void SubWord( uint8_t w[4] )
{
    int32_t k;
    for ( k=0; k<4; ++k )
        w[k] = s_box[w[k]];
}

void SubRotRconWord( uint8_t w[4], int32_t k )
{
    uint8_t Rcon = 1, tmp = 0;
    int32_t power = k-1, n;

    /* Rotatin: 0 1 2 3 -> 1 2 3 0 */
    tmp = w[0]; w[0] = w[1]; w[1] = w[2]; w[2] = w[3]; w[3] = tmp;

    /* Run each byte through the s-box */
    SubWord(w);

    /* Compute the Rcon and add it */
    for ( n=0; n<power; ++n )
        Rcon = Rijndael_Mul(Rcon,2);
    w[0] ^= Rcon;
}

void KeyExpansion ( uint8_t eKey[AES_MAX_KEY_SIZE], uint8_t key[AES_256], int32_t Nk, int32_t Nr )
{
    uint8_t w[4];
    int32_t k;

    for ( k=0; k<Nk; ++k )
    {
        eKey[0] = key[4*k]; 
        eKey[1] = key[4*k+1]; 
        eKey[2] = key[4*k+2]; 
        eKey[3] = key[4*k+3]; 
    }

    for ( k=Nk; k<NUM_COL*(Nr+1); ++k )
    {
        w[0] = eKey[4*k-4]; w[1] = eKey[4*k-3]; w[2] = eKey[4*k-2]; w[3] = eKey[4*k-1];
        if ( 0==(k%Nk) )
            SubRotRconWord(w,k/Nk);
        else if ( (Nk>6) && (4==(k%Nk)) )
            SubWord(w);
        eKey[4*k]   = eKey[4*(k-Nk)]   ^ w[0];
        eKey[4*k+1] = eKey[4*(k-Nk)+1] ^ w[1];
        eKey[4*k+2] = eKey[4*(k-Nk)+2] ^ w[2];
        eKey[4*k+3] = eKey[4*(k-Nk)+3] ^ w[3];
    }
}

void AddRoundKey( uint8_t state[AES_BLOCK_SIZE], uint8_t key[AES_MAX_KEY_SIZE], int32_t round )
{
    int32_t k;

    for ( k=0; k<AES_BLOCK_SIZE; ++k )
        state[k] ^= key[AES_BLOCK_SIZE*round + k];
}
 
/*                                                 */
/* ---------------- Key Schedule ----------------- */
/* ----------------------------------------------- */

/* ----------------------------------------------- */
/* ------------------- Encrypt ------------------- */
/*                                                 */
void SubBytes( uint8_t state[AES_BLOCK_SIZE] )
{
    int32_t k = 0;

    /* Run each byte through the s-box */
    for ( k=0; k<AES_BLOCK_SIZE; ++k )
        state[k] = s_box[state[k]];
}

void ShiftRows( uint8_t state[AES_BLOCK_SIZE] )
{
    uint8_t tmp; 

    /*
         0  4  8 12      0  4  8 12
         1  5  9 13  ->  5  9 13  1
         2  6 10 14     10 14  2  6
         3  7 11 15     15  3  7 11
     */

    /* No shifting for row 0 */
    /* Left circular shift by 1 */
    tmp       = state[1];
    state[1]  = state[5];
    state[5]  = state[9];
    state[9]  = state[13];
    state[13] = tmp;

    /* Left circular shift by 2 */
    tmp       = state[2];
    state[2]  = state[10];
    state[10] = tmp;
    tmp       = state[6];
    state[6]  = state[14];
    state[14] = tmp;

    /* Left circular shift by 3 */
    tmp       = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7]  = state[3];
    state[3]  = tmp;
}


void MixSingleColumn( uint8_t state[AES_BLOCK_SIZE], int32_t col )
{
    uint8_t c[NUM_COL] = {0};
    uint8_t w[NUM_COL] = {0};
    int32_t k;
    
    /* Get the col'th column */
    for ( k=0; k<NUM_COL; ++k )
        c[k] = state[4*col + k];

    /* Matrix multiply */
    w[0] = Rijndael_Mul(2,c[0]) ^ Rijndael_Mul(3,c[1]) ^ c[2] ^ c[3];
    w[1] = c[0] ^ Rijndael_Mul(2,c[1]) ^ Rijndael_Mul(3,c[2]) ^ c[3];
    w[2] = c[0] ^ c[1] ^ Rijndael_Mul(2,c[2]) ^ Rijndael_Mul(3,c[3]);
    w[3] = Rijndael_Mul(3,c[0]) ^ c[1] ^ c[2] ^ Rijndael_Mul(2,c[3]);

    /* Put mixed column into the state */
    for ( k=0; k<NUM_COL; ++k )
        state[4*col + k] = w[k];
}
void MixColumns( uint8_t state[AES_BLOCK_SIZE] )
{
    int32_t k;

    /* For each column, mix them in through matrix multiplication */
    for ( k=0; k<NUM_COL; ++k )
        MixSingleColumn(state,k);
}

void RijndaelEncrypt( uint8_t state[AES_BLOCK_SIZE], uint8_t eKey[AES_MAX_KEY_SIZE],int32_t Nr )
{
    int32_t round = 0;

    AddRoundKey(state,eKey,round);

    for ( round = 1; round < Nr; ++round )
    {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state,eKey,round);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state,eKey,Nr);
}

/*                                                 */
/* ------------------- Encrypt ------------------- */
/* ----------------------------------------------- */
 
/* ----------------------------------------------- */
/* ------------------- Decrypt ------------------- */
/*                                                 */
void InvSubBytes( uint8_t state[AES_BLOCK_SIZE] )
{
    int32_t k;

    /* Run each byte through the inverse s-box */ 
    for ( k=0; k<AES_BLOCK_SIZE; ++k )
        state[k] = inv_s_box[state[k]];
}

void InvShiftRows( uint8_t state[AES_BLOCK_SIZE] )
{
    uint8_t temp;

    /* 
         0  4  8 12       0  4  8 12
         1  5  9 13  ->  13  1  5  9
         2  6 10 14      10 14  2  6
         3  7 11 15      15  3  7 11
     */

    /* Row 0 is not shifted */

    /* Shift row 1 right circularly by 1 */
    temp      = state[13];
    state[13] = state[9];
    state[9]  = state[5];
    state[5]  = state[1];
    state[1]  = temp;

    /* Shift row 2 right circularly by 2 */
    temp      = state[2];
    state[2]  = state[10];
    state[10] = temp;
    temp      = state[6];
    state[6]  = state[14];
    state[14] = temp;

    /* Shift row 3 right circularly by 3 */
    temp      = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7]  = state[3];
    state[3]  = temp;
}
void InvMixSingleColumn( uint8_t state[AES_BLOCK_SIZE], int32_t col )
{
    uint8_t c[NUM_COL] = {0};
    uint8_t w[NUM_COL] = {0};
    int32_t k;
    
    /* Get the col'th column */
    for ( k=0; k<NUM_COL; ++k )
        c[k] = state[4*col + k];

    /* Matrix multiply */
    w[0] = Rijndael_Mul(c[0],0x0e) ^ Rijndael_Mul(c[1],0x0b) ^
           Rijndael_Mul(c[2],0x0d) ^ Rijndael_Mul(c[3],0x09);
    w[1] = Rijndael_Mul(c[0],0x09) ^ Rijndael_Mul(c[1],0x0e) ^
           Rijndael_Mul(c[2],0x0b) ^ Rijndael_Mul(c[3],0x0d);
    w[2] = Rijndael_Mul(c[0],0x0d) ^ Rijndael_Mul(c[1],0x09) ^
           Rijndael_Mul(c[2],0x0e) ^ Rijndael_Mul(c[3],0x0b);
    w[3] = Rijndael_Mul(c[0],0x0b) ^ Rijndael_Mul(c[1],0x0d) ^
           Rijndael_Mul(c[2],0x09) ^ Rijndael_Mul(c[3],0x0e);

    /* Put mixed column into the state */
    for ( k=0; k<NUM_COL; ++k )
        state[4*col + k] = w[k];
}
void InvMixColumns( uint8_t state[AES_BLOCK_SIZE] )
{
    int32_t k;

    /* For each column, mix them in through matrix multiplication */
    for ( k=0; k<NUM_COL; ++k )
        InvMixSingleColumn(state,k);
}
/*                                                 */
/* ------------------- Decrypt ------------------- */
/* ----------------------------------------------- */


/* ----------------------------------------------- */
/* -------------------- Tests -------------------- */
/*                                                 */

void PrintVec( uint8_t vec[AES_BLOCK_SIZE] )
{
    int32_t k;
    for ( k=0; k<AES_BLOCK_SIZE; ++k )
        printf("%02x",vec[k]);
}

void TestEncrypt( void )
{
    //int32_t k=0;
    int32_t Nk=4, Nr=10;

    /* Plain Text:  00112233445566778899aabbccddeeff */
    uint8_t pt[AES_BLOCK_SIZE] = { 0x00, 0x11, 0x22, 0x33,
                                   0x44, 0x55, 0x66, 0x77,
                                   0x88, 0x99, 0xaa, 0xbb,
                                   0xcc, 0xdd, 0xee, 0xff };

    /* Key:         000102030405060708090a0b0c0d0e0f */
    uint8_t Key[AES_BLOCK_SIZE] = { 0x00, 0x01, 0x02, 0x03,
                                    0x04, 0x05, 0x06, 0x07,
                                    0x08, 0x09, 0x0a, 0x0b,
                                    0x0c, 0x0d, 0x0e, 0x0f };
    //uint8_t ZeroKey[AES_BLOCK_SIZE] = {0};

    uint8_t eKey[AES_MAX_KEY_SIZE] = {0};

    /* Cipher Text: 69c4e0d86a7b0430d8cdb78070b4c55a */

    KeyExpansion(eKey,Key,Nk,Nr);
    //for ( k=0; k<Nr+1; ++k )
    //{
    //    printf("%d\t",k);
    //    PrintVec(eKey+(AES_BLOCK_SIZE*k));
    //    printf("\n");
    //}
    RijndaelEncrypt(pt,eKey,Nr);
    printf("\n");
    PrintVec(pt);
    printf("\n");
}

/*                                                 */
/* -------------------- Tests -------------------- */
/* ----------------------------------------------- */


//#define PARITY8(X) ( ( X    &1) ^ ((X>>1)&1) ^ \
//                     ((X>>2)&1) ^ ((X>>3)&1) ^ \
//                     ((X>>4)&1) ^ ((X>>5)&1) ^ \
//                     ((X>>6)&1) ^ ((X>>7)&1) )
///* Affine function */
//uint8_t f( uint8_t a )
//{
//    uint8_t mat[8] = { 0xf1, 0xe3, 0xc7, 0x8f,
//                       0x1f, 0x3e, 0x7c, 0xf8 };
//    uint8_t bit, mul, ret;
//    int k;
//
//    ret = 0;
//
//    for ( k=0; k<8; ++k )
//    {
//        mul = a & mat[k];
//        bit = (uint8_t) PARITY8(mul);
//        ret = (bit<<k) ^ ret;
//    }
//
//    return (ret^0x63);
//}
//
//uint8_t fInv( uint8_t a )
//{
//    uint8_t mat[8] = { 0x52, 0x29, 0x94, 0x4a,
//                       0x25, 0x92, 0x49, 0xa4 };
//    uint8_t bit, mul, ret;
//    int k;
//
//    ret = 0;
//
//    for ( k=0; k<8; ++k )
//    {
//        mul = a & mat[k];
//        bit = (uint8_t) PARITY8(mul);
//        ret = (bit<<k) ^ ret;
//    }
//
//    return (ret^0x05);
//}
//
//uint8_t s_box( uint8_t a )
//{
//    a = Rijndael_Inv(a);
//    return f(a);
//}
//
//uint8_t s_box_inv( uint8_t a )
//{
//    a = fInv(a);
//    return Rijndael_Inv(a);
//}
//
//uint8_t parity_test ( void )
//{
//    int k = 0;
//    uint8_t p;
//    for ( k=0; k<256; k++ )
//    {
//        p = (uint8_t) PARITY8(k);
//        printf("%02x\t%02x\n",k,p);
//    }
//    return 0;
//}
//
//
//void print_s_box ( void )
//{
//    int k = 0;
//    uint8_t inv;
//    for ( k=0; k<256; ++k )
//    {
//        //inv = Rijndael_Inv((uint8_t)k);
//        //inv = f(inv);
//        inv = s_box((uint8_t)k);
//        printf("%02x, ",inv);
//        if ( 0==((k+1)%16) )
//            printf("\n");
//    }
//    return;
//}
//
//void print_s_box_inv()
//{
//    int k = 0;
//    uint8_t inv;
//    for ( k=0; k<256; ++k )
//    {
//        //inv = Rijndael_Inv((uint8_t)k);
//        //inv = f(inv);
//        inv = s_box_inv((uint8_t)k);
//        printf("%02x, ",inv);
//        if ( 0==((k+1)%16) )
//            printf("\n");
//    }
//    return;
//}
