#include <stdio.h>
#include <stdlib.h>

#include "binrw.h"

int main (int argc, char **argv){

	FILE *file, *file2;
	file = fopen(argv[1], "rb");
    file2 = fopen(argv[2], "wb");

	if(!file || !file2){
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

        writeBin(file2, 278, 9, 0); 
        writeBin(file2, 305, 9, 0); 
        writeBin(file2, 5000, 16, 0);  

        fclose(file);
        fclose(file2);
    }
    return 0;
}