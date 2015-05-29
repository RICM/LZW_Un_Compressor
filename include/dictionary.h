#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sequence.h"
#include "tree.h"

uint16_t increment;
uint16_t eof;
uint16_t clean_dic;

void InitVar();

//#define increment 259
#define eof 257
#define clean_dic 258

pTree Dictionary[259];

// List of code bound to Tree
typedef struct decode_map_t{
	uint16_t code;
	pSequence sequence;
	struct decode_map_t *succ;
} DecodeMap;

typedef DecodeMap *pDecodeMap;
pTree insertSeqTree(pSequence seq, pTree dic[]);
pTree isPresentEncode(pSequence w, pTree dic[]);

pTree est_dans_dico(pSequence seq, pTree t);

#endif
