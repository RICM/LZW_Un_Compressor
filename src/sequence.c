
#include "sequence.h"

void print_sequence(pSequence seq){
	pSequence tmp = seq;
	while(tmp != NULL){
		printf("%d ", tmp->elem);
		tmp = tmp->succ;
	}
}

void print_sequence_char(pSequence seq){
	pSequence tmp = seq;
	while(tmp != NULL){
		printf("%c ", tmp->elem);
		tmp = tmp->succ;
	}
}

pSequence add_to_tail(pSequence seq, uint16_t elem){
	pSequence newSeq = malloc(sizeof(Sequence));
	newSeq->elem = elem;
	newSeq->succ = NULL;

	if(seq == NULL)
		return newSeq;
	else{
		pSequence tmp = seq;
		while(tmp->succ != NULL)
			tmp = tmp->succ;
		tmp->succ = newSeq;
		return seq;
	}
}

void copySequence(pSequence seq, pSequence *newSeq){
	pSequence tmp = seq;
	while(tmp != NULL){
		*newSeq = add_to_tail(*newSeq, tmp->elem);
		tmp = tmp->succ;
	}
}

void freeSequenceList(pSequence *seq){
	pSequence tmp;
	while(*seq != NULL){
		tmp = *seq;
		*seq = (*seq)->succ;
		free(tmp);
	}
}