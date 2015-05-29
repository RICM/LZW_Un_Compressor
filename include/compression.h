#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dictionary.h"
#include "binrw.h"

void compress(FILE *fr, FILE *fw);

void decompress(FILE *fr, FILE *fw);