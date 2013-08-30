#include "rijndael.h"
#include <string.h>

struct _cipherkey
{
    int length;        /**< Key length (16, 24, or 32) */
    uchar ck[MAXKEY];  /**< Cipher Key */
    uchar eck[MXEKEY]; /**< Expanded Cipher Key */
    int Nb;            /**< The number of columns in the state (always 4) */
    int Nk;            /**< Number of 32 bit words in the cipher key (4, 6, or 8) */
    int Nr;            /**< The number of rounds (10, 12, or 14) */
    int current_round; /**< Keeps track of the rounds */
};

typedef struct _cipherkey CK;
typedef struct _cipherkey * pCK;

#define ERROR_CHK(ERR) if ( SUCCESS!=ERR ) { goto end; }
#define ARG_CHK(ARGS) if ( ARGS ) { error = INVARG; goto end; }

/* Sets the cipher key structure based on the key and the key length */
static int set_cipher( pCK ck, uchar * key, int keylen )
{
    int error = SUCCESS;
    return error;
}

/* */
static int AddRoundKey( uchar * state, pCK ck ) 
{ 
    int error = SUCCESS;
    return error;
}

/* Defines a Rijndael round */
static int Round( uchar * state, pCK ck ) 
{ 
    int error = SUCCESS;
    return error;
}
 
/* Defines the final round to rijndael */
static int FinalRound( uchar * state, pCK ck ) 
{ 
    int error = SUCCESS;
    return error;
}

/* Encrypts state */
static int encrypt( uchar * state, pCK ck )
{
    int error = SUCCESS;
    int Nr, k;
    
    ARG_CHK(!(state && ck) );

    /* Key expansion is all ready done. */
    Nr = ck->Nr;

    /* Add round key */
    error = AddRoundKey(state,ck);
    ERROR_CHK(error);

    /* Loop through rounds */
    for (k=1; k<Nr; ++k)
    {
        error = Round(state,ck);
        ERROR_CHK(error);
    }

    /* Final round */
    error = FinalRound(state,ck);
end:
    return error;
}

/* Decrypts state */
static int decrypt( uchar * state, pCK ck )
{
    int error = SUCCESS;
    return error;
}

/* ------------------------------------------------------------------ */

int rijndael_encrypt( uchar * out, uchar * in, uchar * key, int keylen )
{
    int error = SUCCESS;
    CK cipher = {0};

    /* Set up cipher based on key */
    error = set_cipher(&cipher,key,keylen);
    if (SUCCESS!=error) {
        goto end;
    }
    /* Copy invec into state_enc */
    memcpy(out,in,STLEN);
    /* encrypt */
    error = encrypt(out,&cipher);
end:
    return error;
}

int rijndael_decrypt( uchar * out, uchar * in, uchar * key, int keylen )
{
    int error = SUCCESS;
    CK cipher = {0};

    /* Set up cipher based on key */
    error = set_cipher(&cipher,key,keylen);
    if (SUCCESS!=error) {
        goto end;
    }
    /* Copy invec into state_enc */
    memcpy(out,in,STLEN);
    /* decrypt */
    error = decrypt(out,&cipher);
end:
    return error;
}



