#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <rijndael.h>
#include <rijndael_field.h>

/* Generates random byte array that is n long */
uint32_t random_bytes(uint8_t * byte_arr, uint32_t n, uint32_t seed )
{
    uint32_t rndnum, k=0;
    void * dest = (void*) byte_arr;
    const void * src = &rndnum;

    srand(seed);
    while ( n ) 
    {
        rndnum = (uint32_t) rand();
        if ( n > 4 )
            memcpy(dest,src,4);  
        else 
            memcpy(dest,src,n);
        k++;
        n -= 4;
        dest = (void*)(byte_arr+4*k);
    }
    return 0;
}

void Test01( void )
{
    uint8_t rnd[10] = {0};
    uint8_t a,b,c;
    uint32_t random = 0;
    int32_t k;

    printf("\t*** Starting first test ***\n");
    printf("Testing field arithmetic\n\n");

    random_bytes(rnd,10,1);
    printf("Inversion Test\n");
    for(k=0; k<10; k++)
    {
        a = rnd[k];
        b = Rijndael_Inv(a);
        c = Rijndael_Mul(a,b);
        if(1!=c)
            printf("[%d]:\tERROR\n",k);
        else
            printf("[%d]:\tSUCCESS\n",k);
    }
}

int main ( int argc, char ** argv )
{
    Test01();
    return 0;
}
