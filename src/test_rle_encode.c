#include <stdio.h>

#include "rle.h"

int main(int argc, char **argv) {
	FILE *in;
	FILE *out;

	in = fopen(argv[1], "rb");
	out = fopen(argv[2], "wb");

	run_length_encode(in, out);

	return 0;

}