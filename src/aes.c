#include "aes.h"
#include <string.h>

static void SubRotRcon( uchar *w, int k );
static void SubWord( uchar *w );
static void RotWord( uchar *w );
static void Rotate( uchar *w, int n );
static uchar SubBytes( uchar x );
static void  KeyExpansion( uchar *key, uchar *w, int Nk );
 

/* Internal functions */
uchar SubBytes( uchar x )
{
    return 0;
}

static void  KeyExpansion( uchar *key, uchar *w, int Nk )
{
    uchar tmp[4] = {0};
    int i, Nb, Nr;

    /* Set length dependent values */
    Nb = 4;
    switch(Nk)
    {
    case 16:
        Nr = 10;
        break;
    case 24:
        Nr = 12;
        break;
    case 32:
        Nr = 14;
        break;
    }

    /* Expand initial part of the key */
    for ( i=0; i<Nk; ++i )
    {
        w[4*i+0] = key[4*i+0];
        w[4*i+1] = key[4*i+1];
        w[4*i+2] = key[4*i+2];
        w[4*i+3] = key[4*i+3];
    }
    /* Expand the rest of the key */
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

static void SubRotRcon( uchar *w, int k )
{
    RotWord(w);
    SubWord(w); 
    /* w[0] = 0x02^(k-1); in the GF(256) */
}

static void SubWord( uchar *w )
{
    w[0] = SubBytes(w[0]); w[1] = SubBytes(w[1]); w[2] = SubBytes(w[2]); w[3] = SubBytes(w[3]); 
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

