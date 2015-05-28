#include <stdio.h>
#include <stdlib.h>

#include "binwr.h"

int main (int argc, char **argv){

	FILE *file;
	file = fopen(argv[0], "r");

	if(!file){
        fprintf(stderr, "Error : file is inaccessible.\n");
        return 1;
    }
    else{
        uint8_t tmp = readBin(file, 8);
        displayBinary(tmp);
    }
    return 0;
}