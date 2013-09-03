#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <rijndael.h>

/* Generates random byte array that is n long */
uint32_t random_bytes(uint8_t * byte_arr, uint32_t n, uint32_t seed )
{
    uint32_t rndnum, k=0;

    srand(seed);
    while ( n ) 
    {
        rndnum = (uint32_t) rand();
        if ( n > 4 )
            memcpy(byte_arr+4*k,rndnum,4);  
        else 
            memcpy(byte_arr,rndnum,n);
        k++;
        n -= 4;
    }
}
void Test01( void )
{
    uint8_t rnd[4] = {0};
    uint32_t random = 0;
    printf("\t*** Starting first test ***\n");
    printf("Testing field arithmetic\n\n");

        
}

int main ( int argc, char ** argv )
{
    Test01();
    return 0;
}
