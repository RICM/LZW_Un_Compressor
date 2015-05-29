#include <stdio.h>
#include <stdlib.h>

#include "binrw.h"

int main (int argc, char **argv){

	FILE *file;
	file = fopen(argv[1], "wb");

	if(!file){
        fprintf(stderr, "Error : file is inaccessible.\n");
        return 1;
    }
    else{
        uint16_t tmp;

        initBuffer();

        writeBin(file, 259, 9, 0);
        writeBin(file, 305, 10, 0); 
        writeBin(file, 5000, 16, 1);

        fclose(file);

        file = fopen(argv[1], "rb");
        if(!file){
            fprintf(stderr, "Error : file is inaccessible.\n");
            return 1;
        }
        else{
            tmp = readBin(file, 9);
            printf("\t\t%d\n\n", tmp);
            tmp = readBin(file, 10);
            printf("\t\t%d\n\n", tmp);
            tmp = readBin(file, 16);
            printf("\t\t%d\n\n", tmp);

            fclose(file);
        }
        
    }
    return 0;
}