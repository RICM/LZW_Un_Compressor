#include "dictionary.h"

void InitVar() {
	increment = 256;
	eof = 257;
	clean_dic = 258;
}

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

/* Manipulation du dictionnaire */
pTree est_dans_dico(pSequence seq, pTree t){
	if (seq == NULL) {
		return NULL;
	}
	else {
		pSequence w = seq;
		pTree temp = t;
		if((temp == NULL)||(temp->ascii > w->elem)){
			return NULL;
		}
		else {
		  	if(w->elem != temp->ascii){
			    if(w->succ == NULL) return temp;
			    return est_dans_dico(w, temp->left);
	  		}
	  		else {
			  	w=w->succ;
			  	if (w != NULL)
			  	{
			  		if (temp->right != NULL)
			  		return est_dans_dico(w, temp->right);
			  		else
			  			return NULL;
			  	}

			  	else return temp;
			  }
			}
  	}
}

/* Function used to insert an entity in a tree */
pTree insertInTree(pTree treeToInsert, uint8_t toInsert){
	int increment = 259; // to be modified
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
		pTree newTree = createTree(treeToReturn->ascii, treeToReturn->code, treeToReturn->left, treeToReturn->right);
		treeToReturn->ascii=toInsert;
		treeToReturn->code=increment;
		treeToReturn->left=newTree;
		treeToReturn->right=NULL;
		increment++;
		return treeToReturn;
	}
}

/* Function used to insert a sequence */
pTree add_to_dictionary(pSequence seq, pTree dic[]){
	int increment = 259; // to be modified
	if (seq->succ == NULL){
		return dic[seq->elem];
	}
	pTree toTest = isPresentEncode(seq, dic);
	pTree save = NULL;
	if (toTest != NULL){
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
		}
		if (toTest->ascii == seqAscii && seq->succ != NULL){
			seq = seq->succ;
			if (toTest->right == NULL){
				pTree newTree = malloc(sizeof(tree));
				newTree->ascii = seq->elem;
				newTree->code = increment;
				increment++;
				newTree->left = NULL;
				newTree->right = NULL;
				toTest->right = newTree;
				return newTree;
			}else{
				toTest = toTest->right;
			}
		}else{
			toTest = insertInTree(save, seqAscii);
			ok = 0;
		}
	}
	return toTest;
}