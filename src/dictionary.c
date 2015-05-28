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
	printf("to insert vaut : %d\n", toInsert);
	int increment = 259;
	pTree treeToReturn = treeToInsert;
	if (treeToReturn == NULL)
		printf("first if\n");
		treeToReturn = createTree(toInsert, increment, NULL, NULL); // to replace nextCode
		increment++;
	while(treeToReturn != NULL && treeToReturn->ascii < toInsert){
		printf("while insertInTree\n");
		treeToReturn = treeToReturn->left;
	}
	if(treeToReturn == NULL){
		pTree newTree = createTree(toInsert, increment, NULL, NULL);
		increment++;
		treeToReturn->left = newTree;
		printf("new Tree element : %d | %d\n",treeToReturn->ascii, treeToReturn->code );
		printf("insert sucess\n");
		return newTree;
	}else{
		pTree newTree = createTree(toInsert, increment, treeToReturn->left, NULL);
		increment++;
		treeToReturn->left = newTree;
		printf("new Tree element : %d | %d\n",treeToReturn->ascii, treeToReturn->code );
		printf("insert sucess\n");
		return newTree;
	}
}

/* Function used to insert a sequence */
pTree insertSeqTree(pSequence seq, pTree dic[]){
	if (seq->succ == NULL){
		return dic[seq->elem];
	}
	pTree toTest = isPresentEncode(seq, dic);
	pTree save = NULL;
	if (toTest != NULL)
		return toTest;
	toTest=dic[seq->elem];
	seq = seq->succ;
	int ok = 1;
	while (ok == 1){
		printf("boucle 1\n");
		save = toTest;
		uint8_t seqAscii = seq->elem;
		while(toTest != NULL && toTest->ascii < seqAscii){
			printf("boucle 2\n");
			printf("%d\n", toTest->ascii);
			toTest = toTest->left;
		}
		printf("seqAscii vaut %d\n", seqAscii);
		printf("toTest->ascii vaut %d\n", toTest->ascii);
		if (toTest->ascii == seqAscii && seq->succ != NULL){
			printf("if 1\n");
			seq = seq->succ;
			if (toTest->right == NULL){
				printf("if 2\n");
				seqAscii = seq->elem;
				toTest = insertInTree(save, seqAscii);
				return toTest;
			}
			toTest = toTest->right;
		}else{
			printf("else\n");
			toTest = insertInTree(save, seqAscii);
			ok = 0;
		}
	}
	return toTest;
}