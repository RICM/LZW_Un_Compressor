#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tree_t tree;

struct tree_t{
	uint8_t ascii;
	uint16_t code;
	struct tree_t* left;
	struct tree_t* right;
};

typedef tree *pTree;

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right);

#endif
