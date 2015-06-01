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

uint16_t nextCode;

void initVar();

pTree Dictionary[259];

// List of code bound to Tree
typedef struct decode_map_t{
	uint16_t code;
	pSequence sequence;
	struct decode_map_t *succ;
} DecodeMap;

typedef DecodeMap *pDecodeMap;

pDecodeMap DecodeDictionary;

int numberElemDic(pTree dic[]);
pTree add_to_dictionary(pSequence seq, pTree dic[]);
pTree isPresentEncode(pSequence w, pTree dic[]);

int isPresentInDico(pSequence, pTree dic [], pTree *toReturn);
int isPresentInTree(pSequence seq, pTree t, pTree *toReturn);

pTree findElem(pSequence seq, pTree t);
pTree findElemDico(pSequence seq, pTree dic[]);

pDecodeMap addToDecodeMap(pSequence seq, uint16_t code, pDecodeMap map);
pSequence findCode(uint16_t code, pDecodeMap map);

void freeDictionary();

#endif
