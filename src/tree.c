#include "tree.h"

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right){
	pTree toReturn = malloc (sizeof(tree));
	toReturn->ascii = ascii;
	toReturn->code = code;
	toReturn->left = left;
	toReturn->right = right;
	return toReturn;
}