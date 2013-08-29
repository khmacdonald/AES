CC=gcc
CFLAGS=
LFLAGS=

AesMain: aes.o
	$(CC) -o AesMain AesMain.c aes.o -I includes

aes.o:
	$(CC) -c aes.c -I includes

clean:
	rm AesMain aes.o
