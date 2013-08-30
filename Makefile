CC = gcc

AesMain:rijndael.o
	$(CC) -o AesMain AesMain.c rijndael.o -I includes

rijndael.o:
	$(CC) -c rijndael.c -I includes

clean:
	rm *.o AesMain
