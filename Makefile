#-------------------------------------------------
#                    VARIABLES
#-------------------------------------------------
CC = gcc
CFLAGS = -g -Wall -pedantic -O3 -std=c99 -Iinclude/
LFLAGS = -L$(DIR_LIB)
EXEC = lzw test_sequence test_dic test_binrw test_compress test_decompress test_sequence bindump test_encap
DEBUG = 0
DEBUG_BINRW_LEVEL = 0
DEBUG_COMPRESSION_LEVEL = 0

DIR_INCLUDE = include/
DIR_SRC = src/
DIR_LIB = lib/
DIR_TGT = target/

LFLAGS = -L$(DIR_LIB)
LIBS = -ltokenize

#-------------------------------------------------
#                     LINKINGS
#-------------------------------------------------
all: $(EXEC)

lzw: $(DIR_TGT)main.o $(DIR_TGT)compression.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o $(DIR_TGT)binrw.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)compression.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o $(DIR_TGT)binrw.o
	@echo -e

bindump: $(DIR_TGT)bindump.o $(DIR_TGT)binrw.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)binrw.o
	@echo -e

test_sequence: $(DIR_TGT)test_sequence.o $(DIR_TGT)sequence.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)sequence.o
	@echo -e

test_tree: $(DIR_TGT)test_tree.o $(DIR_TGT)tree.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)tree.o
	@echo -e

test_dic: $(DIR_TGT)test_dic.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o
	@echo -e

test_binrw: $(DIR_TGT)test_binrw.o $(DIR_TGT)binrw.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)binrw.o
	@echo -e

test_compress: $(DIR_TGT)test_compress.o $(DIR_TGT)compression.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o $(DIR_TGT)binrw.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)compression.o $(DIR_TGT)binrw.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o
	@echo -e

test_decompress: $(DIR_TGT)test_decompress.o $(DIR_TGT)compression.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o $(DIR_TGT)binrw.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)compression.o $(DIR_TGT)binrw.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o $(DIR_TGT)sequence.o
	@echo -e

test_encap: $(DIR_TGT)test_encap.o $(DIR_TGT)binrw.o $(DIR_TGT)encapsulate.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)binrw.o $(DIR_TGT)encapsulate.o
	@echo -e

#-------------------------------------------------
#                   DEPENDENCIES
#-------------------------------------------------

$(DIR_TGT)test_sequence.o: $(DIR_SRC)test_sequence.c $(DIR_INCLUDE)sequence.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)bindump.o: $(DIR_SRC)bindump.c $(DIR_INCLUDE)binrw.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)test_tree.o: $(DIR_SRC)test_tree.c $(DIR_INCLUDE)tree.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)test_dic.o: $(DIR_SRC)test_dic.c $(DIR_INCLUDE)dictionary.h $(DIR_INCLUDE)tree.h $(DIR_INCLUDE)sequence.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)test_binrw.o: $(DIR_SRC)test_binrw.c $(DIR_INCLUDE)binrw.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)test_compress.o: $(DIR_SRC)test_compress.c $(DIR_INCLUDE)compression.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)test_decompress.o: $(DIR_SRC)test_decompress.c $(DIR_INCLUDE)compression.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)compression.o: $(DIR_SRC)compression.c $(DIR_INCLUDE)compression.h $(DIR_INCLUDE)binrw.h $(DIR_INCLUDE)dictionary.h 
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS) -DDEBUG_COMPRESSION_LEVEL=$(DEBUG_COMPRESSION_LEVEL)
	@echo -e

$(DIR_TGT)sequence.o: $(DIR_SRC)sequence.c $(DIR_INCLUDE)sequence.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)dictionary.o: $(DIR_SRC)dictionary.c $(DIR_INCLUDE)dictionary.h $(DIR_INCLUDE)tree.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)tree.o: $(DIR_SRC)tree.c $(DIR_INCLUDE)tree.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)binrw.o: $(DIR_SRC)binrw.c $(DIR_INCLUDE)binrw.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS) -DDEBUG_BINRW_LEVEL=$(DEBUG_BINRW_LEVEL)
	@echo -e

<<<<<<< HEAD
$(DIR_TGT)test_encap.o: $(DIR_SRC)test_encap.c $(DIR_INCLUDE)encapsulate.h
=======
$(DIR_TGT)main.o: $(DIR_SRC)main.c $(DIR_INCLUDE)compression.h
>>>>>>> 927df8b319fb8edb3be395cbe45c20ddcbd6b7cc
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

<<<<<<< HEAD
$(DIR_TGT)encapsulate.o: $(DIR_SRC)encapsulate.c $(DIR_INCLUDE)encapsulate.h $(DIR_INCLUDE)binrw.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e
=======
>>>>>>> 927df8b319fb8edb3be395cbe45c20ddcbd6b7cc
#--------------
#    Global
#--------------
$(DIR_TGT)%.o: $(DIR_SRC)%.c
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

#-------------------------------------------------
#                     CLEANING
#-------------------------------------------------

clean:
	rm -f $(DIR_TGT)*
