#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct buf_t{
	uint8_t data;
	uint8_t remain;
} Buffer;

void initBuffer();

void displayBinary(uint16_t n);

uint8_t binEOF();

uint16_t readBin(FILE *f, uint8_t nBits);
