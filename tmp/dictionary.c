#include "dictionary.h"

void initVar() {
	increment = 256;
	eof = 257;
	clean_dic = 258;

	nextCode = 259;
	DecodeDictionary = NULL;
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
	//printf("Est dans dico ?\n");
	if (seq == NULL) {
		return NULL;
	}
	else {
		pSequence w = seq;
		pTree temp = t;
		if((temp == NULL)||(temp->ascii > w->elem)){
			return 0;
		}
		else {
			//printf("Temp ascii %d \n", temp->ascii);
		  	if(w->elem != temp->ascii){
			    if(w->succ == NULL){
			    	return temp; // le bug est là !
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
			  	else 
			  		return temp;
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
	//printf("nextCode = %d\n", nextCode);
	//print_sequence(seq);

	uint8_t way = 0;
	DecodeDictionary = addToDecodeMap(seq, nextCode, DecodeDictionary);

	if (seq->succ == NULL){
		//printf("seq current = %d", seq->elem);
		return dic[seq->elem];
	}

	pTree toTest = isPresentEncode(seq, dic);
	pTree save = NULL;

	// if the seq is already inside
	if (toTest != NULL){
		return toTest;
	}

	toTest=dic[seq->elem];
	seq = seq->succ;

	if (toTest == NULL){
		pTree newTree = malloc(sizeof(tree));
		newTree->ascii = seq->elem;
		newTree->code = nextCode;
		nextCode++;
		newTree->left = NULL;
		newTree->right = NULL;
		dic[seq->elem] = newTree;

		return newTree;
	}

	int ok = 1;
	while (ok){

		//if(toTest != NULL)
			save = toTest;

		//printf("Save : %d\n", save);
		uint8_t seqAscii = seq->elem;

		// we start by looking on the left
		while(toTest != NULL && toTest->ascii < seqAscii){
			toTest = toTest->left;
		}
		//printf("seqAscii %d\n", seqAscii);
		//printf("seq->succ %d\n", seq->succ == NULL);
		//printf("toTest %d\n", toTest == NULL);
		//printf("toTest->ascii %d\n", toTest->ascii);


		if (seq->succ != NULL && toTest->ascii == seqAscii){

			// we look at the next elem in the sequence
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
				//if(!way)
					toTest = toTest->right;
				/*else
					toTest = toTest->left;	
				way = !way;*/
			}
		}else{
			toTest = insertInTree(save, seqAscii);
			ok = 0;
		}
	}
	return toTest;
}

pDecodeMap addToDecodeMap(pSequence seq, uint16_t code, pDecodeMap map){
	pDecodeMap newMap = malloc(sizeof(DecodeMap));
	newMap->code = code;
	newMap->sequence = seq;
	newMap->succ = NULL;

	if(map == NULL)
		return newMap;
	else{
		pDecodeMap tmp = map;
		while(tmp->succ != NULL)
			tmp = tmp->succ;
		tmp->succ = newMap;
		return map;
	}
}

pSequence findCode(uint16_t code, pDecodeMap map){
	pDecodeMap tmp = DecodeDictionary;
	while(tmp != NULL && tmp->code != code)
		tmp = tmp->succ;
	if(tmp == NULL)
		return NULL;
	else
		return tmp->sequence;
}

void freeDictionary(pTree dictionary[259]){
	uint8_t b = 1;
	for(int i=0; i<259; i++){
		freeTree(&dictionary[i]);
		b &= (dictionary[i] == NULL);
	}
	if(!b)
		printf("Failed to free dictionary. Compression or decompression is compromised... Try again !\n");
}