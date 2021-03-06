#ifndef _BINRW_H
#define _BINRW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct buf_t{
	uint16_t data;
	uint8_t remain;
} Buffer;

void initBuffer();

void displayBinary(uint16_t n, uint8_t nOctets);

uint8_t binEOF();

uint16_t readBin(FILE *f, uint8_t nBits);

void writeBin(FILE *f, uint16_t toWrite, uint8_t nBits, uint8_t isFinal);

uint16_t readLast(uint8_t nBits);

void printBufferRead();

void printBufferReadPred();

void flushBufferRead();

#endif