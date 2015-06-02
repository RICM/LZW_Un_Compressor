#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "rle.h"
#include "encapsulate.h"

void usage (){
	printf("correct usage : lzw [-d / -c]\n");
}

void usageCompression (){
	printf("correct usage : lzw [-c] [fileName] [archiveName]\n");
}

void usageCompressionRle (){
	printf("correct usage for RLE compression : lzw [-cl] [fileName] [archiveName]\n");
}

void usageDecompression (){
	printf("correct usage : lzw [–d] [archiveName]\n");
}

void usageDecompressionRle (){
	printf("correct usage for RLE decompression : lzw [–dl] [archiveName]\n");
}

void extension(){
	printf("The name of the archive must countain '.lzw' as extension\n");
	usageCompression();
	printf("or\n");
	usageDecompression();
	printf("or\n");
	usageCompressionRle();
	printf("or\n");
	usageDecompressionRle();
}

int main (int argc, char **argv){
	/* -c/-d nomfichier */
	char tiret = argv[1][0];
	char operation = argv[1][1];
	char operation2 = argv[1][2];
	FILE *file, *file2;
	if ((tiret=='-' && operation=='c') /*|| (tiret=='-' && operation=='c' && operation2=='l')*/  && (argc != 4 && argc != 3)){
		usageCompression();
		return -1;
	}
	if ((tiret=='-' && operation=='c' && operation2=='l')&& (argc != 4 && argc != 3)){
		usageCompressionRle();
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
			fullEncapsulate(&file, &file2, argv[2], argv[3]);
			if(!file || !file2){
		        fprintf(stderr, "Error : File error / inaccessible.\n");
		        return -1;
		    }
		    printf("Running compression...\n");
			if (operation2 == 'l'){
				run_length_encode(file , file2);

			}else{
				compress(file, file2);
			}
			break;
		case 'd' :
			/*
			Decompression treatment
			*/
			if (strstr(argv[2], ".lzw") != NULL) {
				fullDesencapsulate(&file, &file2, argv[2]);
				if(!file || !file2){
			        fprintf(stderr, "Error : File error / inaccessible.\n");
			        return 1;
			    }
			    printf("Running decompression ...\n");
			    if (operation2 == 'l'){
			    	run_length_decode(file, file2);
			    }
		    	decompress(file, file2);
		    }else{
		    	extension();
		    	return -1;
		    }
			break;
	}
	fclose(file);
	fclose(file2);
	return 0;
}