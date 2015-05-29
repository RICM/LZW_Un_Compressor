#include "dictionary.h"
int nextCode = 259;
void InitVar() {
	increment = 256;
	eof = 257;
	clean_dic = 258;
}

int numberElemDic(pTree dic[]){
	int count = 0;
	for (int i = 0; i<258; i++){
		count = count+numberElemTree(dic[i])+1;
	}
	return count;
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
	printf("Est dans dico ?\n");
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
			printf("Temp ascii %d \n", temp->ascii);
		  	if(w->elem != temp->ascii){
			    if(w->succ == NULL){
			    	return NULL; // le bug est là !
			    	// return temp; d'après antoine
			    }
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
	pTree treeToReturn = treeToInsert;
	pTree saveParent = NULL;
	while(treeToReturn != NULL && treeToReturn->ascii < toInsert){
		saveParent = treeToReturn;
		treeToReturn = treeToReturn->left;
	}
	if(treeToReturn == NULL){
		pTree newTree = createTree(toInsert, nextCode, NULL, NULL);
		nextCode++;
		saveParent->left = newTree;
		return newTree;
	}else{
		pTree newTree = createTree(treeToReturn->ascii, treeToReturn->code, treeToReturn->left, treeToReturn->right);
		treeToReturn->ascii=toInsert;
		treeToReturn->code=nextCode;
		treeToReturn->left=newTree;
		treeToReturn->right=NULL;
		nextCode++;
		return treeToReturn;
	}
}

/* Function used to insert a sequence */
pTree add_to_dictionary(pSequence seq, pTree dic[]){
	printf("nextCode = %d\n", nextCode);
	print_sequence(seq);
	if (seq->succ == NULL){
		//printf("seq current = %d", seq->elem);
		return dic[seq->elem];
	}
	pTree toTest = isPresentEncode(seq, dic);
	pTree save = NULL;
	if (toTest != NULL){
		return toTest;
	}
	toTest=dic[seq->elem];
	if (toTest == NULL){
		pTree newTree = malloc(sizeof(tree));
		newTree->ascii = seq->succ->elem;
		newTree->code = nextCode;
		nextCode++;
		newTree->left = NULL;
		newTree->right = NULL;
		dic[seq->elem] = newTree;
		return newTree;
	}
	seq = seq->succ;
	int ok = 1;
	while (ok == 1){
		save = toTest;
		uint8_t seqAscii = seq->elem;
		while(toTest != NULL && toTest->ascii < seqAscii){
			toTest = toTest->left;
		}
		printf("seq->succ %d\n", seq->succ );
		if (seq->succ != NULL && toTest->ascii == seqAscii){
			seq = seq->succ;
			if (toTest->right == NULL){
				pTree newTree = malloc(sizeof(tree));
				newTree->ascii = seq->elem;
				newTree->code = nextCode;
				nextCode++;
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