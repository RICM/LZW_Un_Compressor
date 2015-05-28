#include "tree.h"

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right){
	pTree toReturn = malloc (sizeof(tree));
	toReturn->ascii = ascii;
	toReturn->code = code;
	toReturn->left = left;
	toReturn->right = right;
	return toReturn;
}

void print_tree(pTree tree){
	if (tree == NULL)
		printf("x\n");
	else{
		printf("%d | %d\n", tree->ascii, tree->code);
		printf("Fils gauche : ");
		print_tree(tree->left);
		printf("Fils droit : ");
		print_tree(tree->right);
	}
}