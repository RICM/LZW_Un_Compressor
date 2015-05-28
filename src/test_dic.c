#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main (int argc, char **argv){
	pTree elem1 = createTree(1, 1, NULL, NULL);
	pTree elem2 = createTree(2, 2, elem1, NULL);
	pTree elem3 = createTree(3, 3, elem2, NULL);
	Dictionary[0] = elem3;
	printf("hello\n");
}
