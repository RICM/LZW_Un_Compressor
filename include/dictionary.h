#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sequence.h"

uint16_t increment = 256;
uint16_t eof = 257;
uint16_t clean_dic = 258;

typedef Tree Dictionary[259];

// List of code bound to Tree
typedef struct decode_map_t{
	uint16_t code;
	pSequence sequence;
	struct decode_map_t *succ;
} DecodeMap;

typedef DecodeMap *pDecodeMap

Tree isPresentEncode(pSequence w);
Tree isPresentDecode(uint16_t code);