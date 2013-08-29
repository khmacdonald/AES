#include "aes.h"
#include <string.h>

static void SubRotRcon( uchar *w, int k );
static void SubWord( uchar *w );
static void RotWord( uchar *w );
static void Rotate( uchar *w, int n );
static uchar SubBytes( uchar x );
static void  KeyExpansion( uchar *key, uchar *w, int Nk );
static int set_Nr( int Nk );
static void initial_expansion( uchar *key, uchar *w, int Nk );
static void expand_key( uchar *key, uchar *w, int Nk, int Nr, int Nb );
 

/* Internal functions */
static uchar SubBytes( uchar x )
{
    return 0;
}

static void  KeyExpansion( uchar *key, uchar *w, int Nk )
{
    int i, Nb, Nr;

    /* Set length dependent values */
    Nb = 4;
    Nr = set_Nr(Nk);

    /* Initialize key expansion */
    initial_expansion(key,w,Nk);

    /* Expand the rest of the key */
    expand_key(key,w,Nk,Nr,Nb);

    return;
}

static void SubRotRcon( uchar *w, int k )
{
    RotWord(w);
    SubWord(w); 
    /* w[0] = 0x02^(k-1); in the GF(256) */
}

static void SubWord( uchar *w )
{
    w[0] = SubBytes(w[0]); 
    w[1] = SubBytes(w[1]); 
    w[2] = SubBytes(w[2]); 
    w[3] = SubBytes(w[3]); 
}

static void RotWord( uchar *w )
{
    Rotate(w,1);
}

static void Rotate( uchar *w, int n )
{
    uchar u[4] = {0};
    int k,i;

    for ( i=0; i<4; ++i )
    {
        u[(i+n)%4] = w[i];
    }
    memcpy(w,u,4);
}

static int set_Nr( int Nk )
{
    if (16==Nk)
        return 10;
    if (24==Nk)
        return 12;
    if (32==Nk)
        return 14;
    return -1;
}

static void initial_expansion( uchar *key, uchar *w, int Nk )
{
    int i;
    for ( i=0; i<Nk; ++i )
    {
        w[4*i+0] = key[4*i+0];
        w[4*i+1] = key[4*i+1];
        w[4*i+2] = key[4*i+2];
        w[4*i+3] = key[4*i+3];
    }
    return;
}

static void expand_key( uchar *key, uchar *w, int Nk, int Nr, int Nb )
{
    uchar tmp[4]={0};
    int i;
    for ( i=Nk; i<Nb*(Nr+1); ++i )
    {
        tmp[0] = w[4*i-4];  
	tmp[1] = w[4*i-3];  
	tmp[2] = w[4*i-2];  
	tmp[3] = w[4*i-1]; 
        if ( 0==(i%Nk) )
            SubRotRcon(tmp,i/Nk);
        else if ( (Nk>6) && (4==(i%Nk)) )
            SubWord(tmp);

        w[4*i+0] = w[4*(i-Nk)+0] ^ tmp[0];
        w[4*i+1] = w[4*(i-Nk)+1] ^ tmp[1];
        w[4*i+2] = w[4*(i-Nk)+2] ^ tmp[2];
        w[4*i+3] = w[4*(i-Nk)+3] ^ tmp[3];
    }
    return;
}

