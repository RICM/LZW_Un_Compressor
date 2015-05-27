#include "dictionary.h"

/* Function used to know if a sequence matches */
int isPresentEncode(pSequence seq){
	pSequence w = seq;
	int ispresent = 1;
	Tree left = Dictionary[w->elem];
	Tree right = NULL;
	int ok = 0;
	while (w->succ != NULL && ok == 1){
		w = w->succ;
		right_tree = findElementLeft(initial_tree)->right;
		if (right_tree != NULL){
			left_tree = ispresenttreeright;
			ok = 1;
		}
		else{
			ok = 0;
		}
	}
	return ok;
}

Tree findElementLeft(Tree t, uint8_t elemToFind){
	int trouve = O;
	Tree toreturn;
	while (trouve == 0 && t != null){
		if (t->)
	}
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