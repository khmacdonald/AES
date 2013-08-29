#ifndef AES_H
#define AES_H

#define MAXKEY  32
#define MAXRND  14
#define MXEKEY  MAXKEY*MAXRND

typedef unsigned char uchar;
typedef unsigned int  uint;

struct _state
{
    unsigned char s[16]; /**< A block of Rijndael is 128 bits long */
};

struct _cipherkey
{
    int length;        /**< Key length (16, 24, or 32) */
    uchar ck[MAXKEY];  /**< Cipher Key */
    uchar eck[MXEKEY]; /**< Expanded Cipher Key */
    int Nb;            /**< The number of columns in the state (always 4) */
    int Nk;            /**< Number of 32 bit words in the cipher key (4, 6, or 8) */
    int Nr;            /**< The number of rounds (10, 12, or 14 */
};

typedef struct _state aes_state;
typedef struct _cipherkey aes_cipherkey;

#endif
