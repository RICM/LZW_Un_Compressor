#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"

void usage (){
	printf("correct usage : lzw [-d / -c]\n");
}

void usageCompression (){
	printf("correct usage : lzw [-c] [fileName] [archiveName.lzw]\n");
}

void usageDecompression (){
	printf("correct usage : lzw [–d] [archiveName.lzw]\n");
}

void extansion(){
	printf("The name of the archive must countain '.lzw' as extansion\n");
	usageCompression();
	printf("or\n");
	usageDecompression();
}

int main (int argc, char **argv){
	/* -c/-d nomfichier */
	char tiret = argv[1][0];
	char operation = argv[1][1];
	FILE *file, *file2;
	if (tiret=='-' && operation=='c' && (argc != 4 && argc != 3)){
		usageCompression();
		return -1;
	}
	if (tiret=='-' && operation=='d' && (argc != 4 && argc != 3)){
		usageDecompression();
		return -1;
	}
	if ((argc != 4 && argc != 3) || tiret!='-' || (operation!='d' && operation!='c')){
		usage();
		return -1;
	}
	switch (operation){
		case 'c' :
			/*
			Compression treatment 
			*/
			if (strstr(argv[3], ".lzw") != NULL) {
				file = fopen(argv[2], "rb");
				file2 = fopen(argv[3], "wb");
				if(!file || !file2){
			        fprintf(stderr, "Error : File error / inaccessible.\n");
			        return -1;
			    }
				compress(file, file2);
			}else{
				extansion();
				return -1;
			}
			break;
		case 'd' :
			/*
			Decompression treatment
			*/
			if (strstr(argv[2], ".lzw") != NULL) {
				file = fopen(argv[2], "rb");
				char *filename2 = "FILENAME2";
				file2 = fopen(filename2, "wb");
				if(!file || !file2){
			        fprintf(stderr, "Error : File error / inaccessible.\n");
			        return 1;
			    }
		    	decompress(file, file2);
		    }else{
		    	extansion();
		    	return -1;
		    }
			break;
	}
	fclose(file);
	fclose(file2);
	return 0;
}