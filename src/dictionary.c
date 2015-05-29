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
			t = t->left;
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
			if (w->succ == NULL){
				ispresent = toTest;
			}else{
				right = toTest->right;
			}
		}else{ 
			ok = 0;
		}
		if (right != NULL && w->succ != NULL){
			w = w->succ;
			toTest = findElementRight(right, w->elem);
			if (toTest != NULL){	
				if (w->succ == NULL){
					ispresent = toTest;
				}else{
					left  = toTest->right;
				}
			} else {
				ok = 0;
			}
		}
		else{
			ok = 0;
		}
	}
	return ispresent;
}


/* Function used to insert an entity in a tree */
pTree insertInTree(pTree treeToInsert, uint8_t toInsert){
	int increment = 259;
	pTree treeToReturn = treeToInsert;
	pTree saveParent = NULL;
	while(treeToReturn != NULL && treeToReturn->ascii < toInsert){
		saveParent = treeToReturn;
		treeToReturn = treeToReturn->left;
	}
	if(treeToReturn == NULL){
		pTree newTree = createTree(toInsert, increment, NULL, NULL);
		increment++;
		saveParent->left = newTree;
		return newTree;
	}else{
		pTree newTree = createTree(toInsert, increment, treeToReturn->left, NULL);
		increment++;
		treeToReturn->left = newTree;
		return newTree;
	}
}

/* Function used to insert a sequence */
pTree insertSeqTree(pSequence seq, pTree dic[]){
	printf("dans la fonction \n");
	if (seq->succ == NULL){
		printf("dans le 1 er if\n" );
		return dic[seq->elem];
	}
	pTree toTest = isPresentEncode(seq, dic);
	pTree save = NULL;
	if (toTest != NULL){
		printf("dans le 2 eme if\n" );
		return toTest;
	}
	toTest=dic[seq->elem];
	seq = seq->succ;
	int ok = 1;
	while (ok == 1){
		save = toTest;
		uint8_t seqAscii = seq->elem;
		while(toTest != NULL && toTest->ascii < seqAscii){
			toTest = toTest->left;
			printf("iteration\n");
		}
		if (toTest->ascii == seqAscii && seq->succ != NULL){
			seq = seq->succ;
			if (toTest->right == NULL){
				seqAscii = seq->elem;
				printf("c'est null\n");
				toTest = insertInTree(save, seqAscii);
				return toTest;
			}
			toTest = toTest->right;
		}else{
			toTest = insertInTree(save, seqAscii);
			ok = 0;
		}
	}
	return toTest;
}