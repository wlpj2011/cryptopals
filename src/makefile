IDIR=../include/
CC=gcc
CFLAGS=-I$(IDIR)set1/

ODIR=obj/
LDIR=../lib/

BINDIR=../bin/
LIBS=-lm

_DEPS = set1/BytestreamUtilities.h set1/CheckDecryptUtilities.h
DEPS = $(patsubst %,$(IDIR)%,$(_DEPS))

_OBJ = include/set1/BytestreamUtilities.o include/set1/CheckDecryptUtilities.o 
OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))



$(ODIR)set1/%.o: set1/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)include/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vpath %.c set1
vpath %.h $(IDIR)set1

Challenge1: $(ODIR)set1/Challenge1.o $(OBJ)
#Compiles Challenge 1
	$(CC) -o $(BINDIR)set1/$@.exe $^ $(CFLAGS) $(LIBS)

Challenge2: $(ODIR)set1/Challenge2.o $(OBJ)
#Compiles Challenge 2
	$(CC) -o $(BINDIR)set1/$@.exe $^ $(CFLAGS) $(LIBS)

Challenge3: $(ODIR)set1/Challenge3.o $(OBJ)
#Compiles Challenge 3
	$(CC) -o $(BINDIR)set1/$@.exe $^ $(CFLAGS) $(LIBS)

Challenge4: $(ODIR)set1/Challenge4.o $(OBJ)
#Compiles Challenge 4
	$(CC) -o $(BINDIR)set1/$@.exe $^ $(CFLAGS) $(LIBS)

vpath

.PHONY: clean

clean:
# Removes all object files, dumped cores, and temporary files ending in ~
	find . -name "*.o" -type f -delete
	find ../ -name "*~" -type f -delete


