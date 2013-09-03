CC = gcc

AesMain:rijndael.o rijndael_field.o
	$(CC) -o AesMain AesMain.c rijndael.o -I includes

rijndael.o:
	$(CC) -c rijndael.c -I includes

rijndael_field.o:
	$(CC) -c rijndael_field.c -I includes

clean:
	rm *.o AesMain
