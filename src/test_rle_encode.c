#include <stdio.h>
#include "rle.h"

int main(void) {
	FILE *in;
	FILE *out;

	in = fopen("rle_in", "rb");

	out = fopen("rle_out", "wb");

	run_length_encode(in, out);

	return 0;

}