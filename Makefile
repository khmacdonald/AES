CC=gcc
CFLAGS=
LFLAGS=



AesMain: aes.o
	$(CC) -o AesMain AesMain.c rijndael.o -I includes

rijndeal.o:
	$(CC) -c rijndael.c -I includes

clean:
	rm AesMain aes.o
