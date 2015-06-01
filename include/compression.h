#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dictionary.h"
#include "binrw.h"

/** 
  Compress a file indicated by fr into 
  another file indicated by fw 
*/
void compress(FILE *fr, FILE *fw);

/** 
  Decompress a file indicated by fr into 
  another file indicated by fw 
*/
void decompress(FILE *fr, FILE *fw);

/**
  Test if a value, has to be code on more bits
  and increment nBitCode if so
*/
void incrementNbits(uint16_t value, FILE *fw);