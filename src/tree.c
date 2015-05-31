#include "tree.h"

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right){
	pTree toReturn = malloc (sizeof(tree));
	toReturn->ascii = ascii;
	toReturn->code = code;
	toReturn->left = left;
	toReturn->right = right;
	return toReturn;
}

int numberElemTree(pTree tree){
	if (tree == NULL)
		return 0;
	return (1+numberElemTree(tree->left)+numberElemTree(tree->right));
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

pTree copyTree(pTree tree){
	pTree newTree;
	if(tree != NULL)
		newTree = createTree(tree->ascii, tree->code, copyTree(tree->left), copyTree(tree->right));
	else
		return NULL;
	return newTree;
}

void freeTree(pTree *tree){
	if(*tree != NULL){
		freeTree(&((*tree)->left));
		freeTree(&((*tree)->right));
		*tree = NULL;
	}
}