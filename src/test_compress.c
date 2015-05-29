#include <stdio.h>
#include <stdlib.h>

#include "compression.h"

int main (int argc, char **argv){
	FILE *file, *file2;
	file = fopen(argv[1], "rb");
	file2 = fopen(argv[2], "wb");

	if(!file || !file2){
        fprintf(stderr, "Error : file is inaccessible.\n");
        return 1;
    }
    else{
    	compress(file, file2);
    	fclose(file);
    	fclose(file2);
    }
	return 0;
}