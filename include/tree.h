#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tree_t tree;

typedef tree *pTree;

struct tree_t{
	uint8_t ascii;
	uint16_t code;
	pTree left;
	pTree right;
};



pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right);
