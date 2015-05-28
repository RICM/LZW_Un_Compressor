#include "dictionary.h"

/* Si trouve l'élément dans la partie gauche d'un arbre bin, renvoie l'arbre*/
pTree findElementLeft(pTree t, uint8_t elemToFind){
	int trouve = 0;
	pTree toReturn = NULL;
	printf("elemToFind = %d, first elem = %d\n", elemToFind, t->ascii);
	while (trouve == 0 && t != NULL && t->ascii <= elemToFind){
		if (t->ascii == elemToFind){
			trouve = 1;
			toReturn = t;
			printf("elem trouvé\n");
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
	if (seq == NULL){
		return NULL;
	}
	pSequence w = seq;
	pTree ispresent = NULL;
	pTree toTest = NULL;
	printf("valeur de w->elem = %d\n", w->elem);
	pTree left = dic[w->elem];
	if (w->succ == NULL){
		return left;
	}
	pTree right = NULL;
	int ok = 1;
	while (w->succ != NULL && ok == 1){
		w = w->succ;
		toTest = findElementLeft(left, w->elem);
		if (toTest != NULL){
			printf("to test n'est pas nul\n");
			if (w->succ == NULL){
				ispresent = toTest;
			}else{
				right = toTest->right;
				printf("ispresent a été mis à right\n");
			}
		}else{ 
			ok = 0;
		}
		if (right != NULL && w->succ != NULL){
			printf("on rentre dans le if\n");
			w = w->succ;
			toTest = findElementRight(right, w->elem);
			if (toTest != NULL){
				left = toTest->left;
			} else {
				ok = 0;
			}
		}
		else{
			ok = 0;
		}
		printf("OK vaut %d\n",ok );
	}
	return ispresent;
}