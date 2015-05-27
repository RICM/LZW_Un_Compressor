#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sequence.h"

uint8_t increment = 256;
uint8_t eof = 257;
uint8_t clean_dic = 258;

typedef Tree Dictionary[259];

// List of code bound to Tree
typedef struct decode_map_t{
	uint16_t code;
	Tree *sequence;
	struct decode_map_t *succ;
} DecodeMap;

typedef DecodeMap *pDecodeMap

int isPresentEncode(pSequence w);
int isPresentDecode(uint16_t code);