#-------------------------------------------------
#                    VARIABLES
#-------------------------------------------------
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99 -Iinclude/
LFLAGS = -L$(DIR_LIB)
EXEC = lzw test_sequence
DEBUG = 0

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

test_sequence: $(DIR_TGT)test_sequence.o $(DIR_TGT)sequence.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)sequence.o
	@echo -e

lzw: $(DIR_TGT)main.o $(DIR_TGT)dictionary.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $<
	@echo -e

test_dic: $(DIR_TGT)test_dic.o $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $< $(DIR_TGT)dictionary.o $(DIR_TGT)tree.o
	@echo -e

#-------------------------------------------------
#                   DEPENDENCIES
#-------------------------------------------------

$(DIR_TGT)test_sequence.o: $(DIR_SRC)test_sequence.c $(DIR_INCLUDE)sequence.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e

$(DIR_TGT)test_dic.o: $(DIR_SRC)test_dic.c $(DIR_INCLUDE)dictionary.h $(DIR_INCLUDE)tree.h
	@echo ------------- Generating $@ -------------
	$(CC) -o $@ -c $< $(CFLAGS)
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
