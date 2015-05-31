#include "tree.h"

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right){
	pTree toReturn = malloc (sizeof(tree));
	toReturn->ascii = ascii;
	toReturn->code = code;
	toReturn->left = left;
	toReturn->right = right;
	return toReturn;
}

pTree addLeft(uint8_t ascii, uint16_t code, pTree tree){
	pTree toAdd = createTree(ascii, code, NULL, NULL);
	tree->left = toAdd;
	return tree;
}

pTree addRight(uint8_t ascii, uint16_t code, pTree tree){
	pTree toAdd = createTree(ascii, code, NULL, NULL);
	tree->right = toAdd;
	return tree;
}

int numberElemTree(pTree tree){
	if (tree == NULL)
		return 0;
	return (1+numberElemTree(tree->left)+numberElemTree(tree->right));
}

void print_tree(pTree tree, uint8_t nTab){
	if (tree == NULL)
		printf("x\n");
	else{	
		printnTab(nTab); printf("%d | %d\n", tree->ascii, tree->code);
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

void printnTab(uint8_t nTab){
	for (int i = 0; i < nTab; ++i)
		printf("\t");
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