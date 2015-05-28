#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main (int argc, char **argv){
	pTree elem6 = createTree(7, 7, NULL, NULL);
	pTree elem5 = createTree(10, 10, NULL, elem6);
	pTree elem4 = createTree(4, 4, elem5, NULL);
	pTree elem3 = createTree(3, 3, NULL, elem4);
	pTree elem2 = createTree(2, 2, elem3, NULL);
	pTree elem1 = createTree(1, 1, elem2, NULL);

	Dictionary[1] = elem1;
	pSequence seq = NULL;
	uint8_t el = 1;
	uint8_t el2 = 2;
	uint8_t el3 = 10;
	uint8_t el4 = 7;
	uint8_t el5 = 50;

	pSequence sequence = add_to_tail(seq, el);
	sequence = add_to_tail(sequence, el2);
	sequence = add_to_tail(sequence, el3);
	sequence = add_to_tail(sequence, el4);
	//sequence = add_to_tail(sequence, el5);

	print_sequence(sequence);
	if (sequence == NULL)
		printf("Seq is null\n");
	pTree test = isPresentEncode(sequence, Dictionary);
	if (test != NULL){
		printf("Printing tree\n");
		print_tree(test);
	}
	else
		printf("Not Found Bitch !\n");


	test = est_dans_dico(sequence->succ,Dictionary[1]->left);
	/*if (result == 1)
		printf("%s\n", "Trouvé par recur");
	else
		printf("%s\n", "Non trouvé par recur");*/
	if (test != NULL){
		printf("printing tree\n");
		print_tree(test);
	}
	else
		printf("goodbye\n");
}
