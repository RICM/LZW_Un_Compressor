#include <stdio.h>
#include <stdlib.h>

#include "sequence.h"

int main (int argc, char **argv){
	pSequence seq = add_to_tail(NULL, 64);
	seq = add_to_tail(seq, 42);
	seq = add_to_tail(seq, 0);
	seq = add_to_tail(seq, 255);
	print_sequence(seq);
	return 0;
}