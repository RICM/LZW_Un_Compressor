#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tree_t{
	uint8_t ascii;
	uint16_t code;
	Tree* left;
	Tree* right;
} Tree;

bool isPresent()
