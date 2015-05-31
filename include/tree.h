#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tree_t tree;
//Dans notre structure, descendre à gauche reient à changer la lettre de la position courante
//Descendre à droite correspond à avancer d'une lettre et donc à "valider" la précédente
struct tree_t{
	uint8_t ascii; //Le code de la table ascii correspondant au carac
	uint16_t code; //Le code de compression correspondant
	struct tree_t* left; //Suite gauche
	struct tree_t* right; //Suite droite
};

typedef tree *pTree;

pTree createTree(uint8_t ascii, uint16_t code, pTree left, pTree right);
pTree insertLeft(uint8_t ascii, uint16_t code, pTree *tree);
pTree insertRight(uint8_t ascii, uint16_t code, pTree *tree);

int numberElemTree(pTree tree);
void print_tree(pTree tree, uint8_t nTab);
pTree copyTree(pTree tree);


void freeTree(pTree *tree);

#endif
