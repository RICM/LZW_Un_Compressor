#include <stdio.h>
#include <stdlib.h>

#include "compression.h"

void usage (){
	printf("correct usage : lzw [-d / -c] [FileName]");
}

int main (int argc, char **argv){
	/* -c/-d nomfichier */
	char tiret = argv[0][0];
	char operation = argv[0][1];
	FILE *file, *file2;
	if (argc != 2 || tiret!='-' || (operation!='d' || operation!='c')){
		usage();
		return -1;
	}
	file = fopen(argv[1], "rb");
	file2 = fopen(argv[2], "wb");
	if(!file || !file2){
        fprintf(stderr, "Error : file is inaccessible.\n");
        return 1;
    }
	switch (operation){
		case 'c' :
			/*
			Compression treatment 
			*/
	    	compress(file, file2);
			break;
		case 'd' :
			/*
			Decompression treatment
			*/
		    decompress(file, file2);
			break;
	}
	fclose(file);
	fclose(file2);
	return 0;
}