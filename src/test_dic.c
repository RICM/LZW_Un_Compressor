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
	uint8_t el6 = 70;
	pSequence sequence = add_to_tail(seq, el);
	sequence = add_to_tail(sequence, el2);
	sequence = add_to_tail(sequence, el3);
	sequence = add_to_tail(sequence, el4);
	pSequence sequence2 = add_to_tail(seq, el);
	sequence2 = add_to_tail(sequence2, el2);
	sequence2 = add_to_tail(sequence2, el3);
	sequence2 = add_to_tail(sequence2, el4);
	sequence2 = add_to_tail(sequence2, el5);
	pSequence sequence3 = add_to_tail(seq, el);
	sequence3 = add_to_tail(sequence3, el2);
	sequence3 = add_to_tail(sequence3, el3);
	sequence3 = add_to_tail(sequence3, el4);
	sequence3 = add_to_tail(sequence3, el5);
	sequence3 = add_to_tail(sequence3, el6);

	printf("Sequence 1 :\n");
	print_sequence(sequence);
	printf("\nSequence 2 :\n");
	print_sequence(sequence2);
	printf("\nSequence 3 :\n");
	print_sequence(sequence3);
	printf("\n");
	/*if (sequence == NULL)
		printf("Seq is null\n");
	pTree test = isPresentEncode(sequence, Dictionary);
	if (test != NULL){
		printf("Printing tree\n");
		print_tree(test);
	}
	else
		printf("Not Found Bitch !\n");

	test = est_dans_dico(sequence->succ,Dictionary[1]->left);
	if (result == 1)
		printf("%s\n", "Trouvé par recur");
	else
		printf("%s\n", "Non trouvé par recur");*/
	/*if (test != NULL){
		printf("printing tree\n");
		print_tree(test);
	}
	else
		printf("goodbye\n");
	*/

	printf("Adding to tree\n");
	pTree test2 = insertSeqTree(sequence2, Dictionary);
	if (test2 != NULL){
		printf("Printing tree\n");
		print_tree(test2);
	}

	pTree test3 = insertSeqTree(sequence3, Dictionary);
	if (test3 != NULL){
		printf("Printing tree\n");
		print_tree(test3);
	}
	//print_tree(Dictionary[1]);
}
