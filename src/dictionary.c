#include "dictionary.h"

/* Si trouve l'élément dans la partie gauche d'un arbre bin, renvoie l'arbre*/
pTree findElementLeft(pTree t, uint8_t elemToFind){
	int trouve = 0;
	pTree toReturn = NULL;
	while (trouve == 0 && t != NULL && t->ascii <= elemToFind){
		if (t->ascii == elemToFind){
			trouve = 1;
			toReturn = t;
		} else {
			t = t->left;
		}
	}
	return toReturn;
}

/* Si trouve l'élément dans la partie droite d'un arbre bin, renvoie l'arbre*/
pTree findElementRight(pTree t, uint8_t elemToFind){
	int trouve = 0;
	pTree toReturn = NULL;
	while (trouve == 0 && t != NULL && t->ascii <= elemToFind){
		if (t->ascii == elemToFind){
			trouve = 1;
			toReturn = t;
		} else {
			t = t->right;
		}
	}
	return toReturn;
}

/* Function used to know if a sequence matches */
pTree isPresentEncode(pSequence seq, pTree dic[]){
	if (seq == NULL)
		return NULL;
	pSequence w = seq;
	pTree ispresent = NULL;
	pTree left = dic[w->elem];
	pTree right = NULL;
	int ok = 1;
	while (w->succ != NULL && ok == 1){
		w = w->succ;
		right = findElementLeft(left, w->elem)->right;
		if (right != NULL){
			if (w->succ == NULL){
				ok = 1;
				return right;
			} else {
				ok = 1;
				w = w->succ;
				left = findElementRight(right, w->elem)->left;
			}
		}
		else{
			ok = 0;
		}
	}
	return ispresent;
}