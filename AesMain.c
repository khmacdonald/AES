#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <rijndael.h>
#include <rijndael_field.h>

/* Generates random byte array that is n long */
uint32_t random_bytes(uint8_t * byte_arr, uint32_t m, uint32_t seed )
{
    uint32_t rndnum, k=0;
    int32_t n = (int32_t) m;
    void * dest = (void*) byte_arr;
    const void * src = &rndnum;

    if (n<0)
        return -1;

    srand(seed);
    while ( n>0 ) 
    {
        /* printf("n = %d\n",n); */
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

int inversion_test( void )
{
    uint8_t rnd[10] = {0};
    uint8_t a,b,c;
    int32_t k;
    int errors = 0;

    random_bytes(rnd,10,1);
    printf("  Inversion Test\n");
    for(k=0; k<10; k++)
    {
        a = rnd[k];
        b = Rijndael_Inv(a);
        c = Rijndael_Mul(a,b);
        if(1!=c)
        {
            printf("[%d]:\tERROR\n",k);
            errors++;
        }
        else
            printf("[%d]:\tSUCCESS\n",k);
    }
    return errors;
}

int addition_test( void )
{
    uint8_t a[10]={0};
    uint8_t b[10]={0};
    uint8_t c,d;
    int32_t k=0;
    int errors=0;
    
    printf("  Additions Test\n"); 
    random_bytes(a,10,1);
    random_bytes(b,10,1);
    for(k=0;k<10;++k)
    {
        c=Rijndael_Add(a[k],b[k]);
        d=a[k]^b[k];
        if(d!=c)
        {
            printf("[%d]:\tERROR\n",k);
            errors++;
        }
        else
            printf("[%d]:\tSUCCESS\n",k);
    }
    return errors;
}

int multiplication_test( void )
{
    uint8_t a[10]={0};
    uint8_t b[10]={0};
    uint8_t c,d,e;
    int32_t k=0;
    int errors=0;
    
    printf("  Multiplication Test\n"); 
    random_bytes(a,10,1);
    random_bytes(b,10,2);
    for(k=0;k<10;++k)
    {
        c=Rijndael_Mul(a[k],b[k]);
        e=Long_Mul2(a[k],b[k]);
        if(e!=c)
        {
            printf("[%d]:\tERROR (a=%02x,b=%02x,c=%02x,e=%02x)\n",k,a[k],b[k],c,e);
            errors++;
        }
        else
            printf("[%d]:\tSUCCESS\n",k);
    }
    return errors;
}

void TestField( void )
{
    int errors=0;
    printf("\t*** Starting first test ***\n");
    printf("Testing field arithmetic\n\n");
    errors += inversion_test();
    errors += addition_test();
    errors += multiplication_test();
    printf("Number of test errors: %d\n",errors);
}

int main ( int argc, char ** argv )
{
    //TestField();
    return 0;
}
