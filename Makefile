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
	mkdir -p $(BIN)
	$(CC) -o $(PROJ) $(SRC)$(PROJ).c $(BIN)$(PREREQ).o  $(INC) $(PUBINC)
	mv $(PROJ) $(BIN)$(PROJ)

$(PREREQ).o:
	mkdir -p $(BIN)
	$(CC) -c $(SRC)$(PREREQ).c  $(INC) $(PUBINC)
	mv $(PREREQ).o $(BIN)$(PREREQ)

clean: 
	rm *.o includes/*~ src/*~ o
	rm -rf $(BIN)

run:
	$(BIN)/$(PROJ) $(ARG)

