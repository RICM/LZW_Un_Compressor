#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Structure for octet sequences
typedef struct seq_t{
	uint8_t elem;
	struct seq_t *succ;
} Sequence;

typedef Sequence *pSequence;

void print_sequence(pSequence seq);

pSequence add_to_tail(pSequence seq, uint8_t elem);

void freeSequenceList(pSequence seq);