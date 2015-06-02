#include <stdio.h>

#include "rle.h"

int main(int argc, char **argv) {
	FILE *in;
	FILE *out;

	in = fopen(argv[1], "rb");
	out = fopen(argv[2], "wb");

	run_length_decode(in, out);

	return 0;

}