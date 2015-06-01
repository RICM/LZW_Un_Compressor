#include <stdio.h>
#include "rle.h"

int main(void) {
	FILE *in;
	FILE *out;

	in = fopen("rle_out", "rb");

	out = fopen("rle_decoded", "wb");

	run_length_decode(in, out);

	return 0;

}