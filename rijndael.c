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
