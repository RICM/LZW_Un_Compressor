#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main (int argc, char **argv){
	pTree elem1 = createTree(1, 1, NULL, NULL);
	pTree elem2 = createTree(2, 2, elem1, NULL);
	pTree elem3 = createTree(3, 3, elem2, NULL);
	Dictionary[1] = elem3;
	pSequence seq = NULL;
	uint8_t el = 1;
	uint8_t el2 = 3;
	pSequence sequence = add_to_tail(seq, el);
	sequence = add_to_tail(sequence, el2);
	print_sequence(sequence);
	if (sequence == NULL)
		printf("Seq is null\n");
	printf("ok\n");
	pTree test = isPresentEncode(sequence, Dictionary);
	if (test != NULL){
		printf("printing tree\n");
		print_tree(test);
	}
	else
		printf("goodbye\n");
}
