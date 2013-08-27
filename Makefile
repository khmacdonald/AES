PROJ   = AesMain
PREREQ = aes

CFLAGS =
LFLAGS =

ARG    =

CODE   = ../
PUBINC = -I $(CODE)includes 
INC    = -I includes
SRC    = src/
BIN    = bin/

CC     = gcc

$(PROJ): $(PREREQ).o
	$(CC) -o $(PROJ) $(SRC)$(PROJ).c $(BIN)$(PREREQ).o  $(INC) $(PUBINC)
	mv $(PROJ) $(BIN)

$(PREREQ).o:
	$(CC) -c $(SRC)$(PREREQ).c  $(INC) $(PUBINC)
	mv $(PREREQ).o $(BIN)

clean: 
	rm *.o includes/*~ src/*~ $(BIN)$(PROJ) $(BIN)*.o

run:
	./$(PROJ) $(ARG)

