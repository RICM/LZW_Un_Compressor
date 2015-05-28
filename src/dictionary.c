#include "dictionary.h"

/* Function used to know if a sequence matches */
Tree isPresentEncode(pSequence seq){
	if (seq == NULL)
		return NULL;
	pSequence w = seq;
	Tree ispresent = NULL;
	Tree left = Dictionary[w->elem];
	uint8_t current = w->elem;
	Tree right = NULL;
	int ok = 1;
	while (w->succ != NULL && ok == 1){
		w = w->succ;
		right = findElementLeft(left, w->elem)->right;
		if (right_tree != NULL){
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

/* Si trouve l'élément dans la partie gauche d'un arbre bin, renvoie l'arbre*/
Tree findElementLeft(Tree t, uint8_t elemToFind){
	int trouve = O;
	Tree toreturn == NULL;
	while (trouve == 0 && t != null && t->ascii <= elemToFind){
		if (t->ascii == elemToFind){
			trouve = 1;
			toreturn = t;
		} else {
			t = t->left;
		}
	}
	return toreturn;
}

/* Si trouve l'élément dans la partie droite d'un arbre bin, renvoie l'arbre*/
Tree findElementRight(Tree t, uint8_t elemToFind){
	int trouve = O;
	Tree toreturn == NULL;
	while (trouve == 0 && t != null && t->ascii <= elemToFind){
		if (t->ascii == elemToFind){
			trouve = 1;
			toreturn = t;
		} else {
			t = t->right;
		}
	}
	return toreturn;
}



/* Function used to know if a sequence matches */
int isPresentDecode(uint16_t code){
	pDecodeMap elem;
	int ispresent = 0;
	while (pDecodeMap->succ != NULL && ispresent = 0){
		if (pDecodeMap->code == code)
			ispresent = 1;
	}
	return ispresent;
}