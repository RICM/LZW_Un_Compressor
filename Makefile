#-------------------------------------------------
#                    VARIABLES                    
#-------------------------------------------------
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99 -Iinclude/
LFLAGS = -L$(DIR_LIB)
EXEC = lzw_compress
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

lzw_compress: $(DIR_TGT)main.o
	@echo ------------- Generating $@ -------------
	$(CC) -o $(DIR_TGT)$@ $<
	@echo -e

#-------------------------------------------------
#                   DEPENDENCIES                  
#-------------------------------------------------

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
	
