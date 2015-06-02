#ifndef _SEQUENCE_H
#define _SEQUENCE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Structure for octet sequences
typedef struct seq_t{
	uint16_t elem;
	struct seq_t *succ;
} Sequence;

typedef Sequence *pSequence;

void print_sequence(pSequence seq);
void print_sequence_char(pSequence seq);

pSequence add_to_tail(pSequence seq, uint16_t elem);

void copySequence(pSequence seq, pSequence *newSeq);

void freeSequenceList(pSequence *seq);

int sizeSequence(pSequence seq);

#endif