#include <stdio.h>
#include <stdlib.h>

#include "binrw.h"

int main (int argc, char **argv){

	FILE *file;
	file = fopen(argv[1], "rb");

	if(!file){
        fprintf(stderr, "Error : file is inaccessible.\n");
        return 1;
    }
    else{
        uint16_t tmp;

        initBuffer();

        while(!binEOF() && !feof(file)){
            tmp = readBin(file, 10);
            displayBinary(tmp);
            printf("\n");
        }      
    }
    return 0;
}