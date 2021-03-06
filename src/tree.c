#include "tree.h"

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right){
	pTree toReturn = malloc (sizeof(tree));
	toReturn->ascii = ascii;
	toReturn->code = code;
	toReturn->left = left;
	toReturn->right = right;
	return toReturn;
}

pTree insertLeft(uint8_t ascii, uint16_t code, pTree *tree){
	pTree toAdd = createTree(ascii, code, (*tree)->left, NULL);
	(*tree)->left = toAdd;
	return toAdd;
}

pTree insertRight(uint8_t ascii, uint16_t code, pTree *tree){
	pTree toAdd = createTree(ascii, code, NULL, (*tree)->right);
	(*tree)->right = toAdd;
	return toAdd;
}

int numberElemTree(pTree tree){
	if (tree == NULL)
		return 0;
	return (1+numberElemTree(tree->left)+numberElemTree(tree->right));
}

void printnTab(uint8_t nTab){
	for(int i=0; i<nTab; i++)
		printf("\t");
}

void print_tree(pTree tree, uint8_t nTab){
	if (tree == NULL)
		printf("\tx\n");
	else{	
		printf("\t%d | %d\n", tree->ascii, tree->code);
		printnTab(nTab); printf("Fils gauche : ");
		if(nTab == 8)
			print_tree(tree->left, 1);
		else
			print_tree(tree->left, nTab+1);
		printnTab(nTab); printf("Fils droit : ");
		if(nTab == 8)
			print_tree(tree->right, 1);
		else
			print_tree(tree->right, nTab+1);
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
		free(*tree);
		*tree = NULL;
	}
}