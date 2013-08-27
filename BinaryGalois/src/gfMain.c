#include <stdlib.h>

#include "gf_8bit.h"
#include "Rijndael.h"

#define ARGCHK(cond,str,label) if ( cond ) { printf(str); goto label; }

int main ( int argc, char ** argv )
{

    if ( argc<1 || argv[0] == '\0' )
        printf("%s is an invalid command\n",argv[0]);

    TestEncrypt();

    return 0;
}