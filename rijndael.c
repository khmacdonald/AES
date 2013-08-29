#include "aes.h"
#include <string.h>

struct _cipherkey
{
    int length;        /**< Key length (16, 24, or 32) */
    uchar ck[MAXKEY];  /**< Cipher Key */
    uchar eck[MXEKEY]; /**< Expanded Cipher Key */
    int Nb;            /**< The number of columns in the state (always 4) */
    int Nk;            /**< Number of 32 bit words in the cipher key (4, 6, or 8) */
    int Nr;            /**< The number of rounds (10, 12, or 14) */
};

typedef struct _cipherkey CK;
typedef struct _cipherkey * pCK;

/* Sets the cipher key structure based on the key and the key length */
static int set_cipher( pCIPHERKEY ck, uchar * key, int keylen )
{
	int error = SUCCESS;
	return error;
}

/* Encrypts state */
static int encrypt( uchar * state, pCIPHERKEY ck )
{
	int error = SUCCESS;
	return error;
}

/* Decrypts state */
static int decrypt( uchar * state, pCIPHERKEY ck )
{
	int error = SUCCESS;
	return error;
}

/* ------------------------------------------------------------------ */

int rijndael_encrypt( uchar * out, uchar * in, uchar * key, int keylen )
{
	int error = SUCCESS;
	CIPHERKEY cipher = {0};

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



