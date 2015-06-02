#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "rle.h"
#include "encapsulate.h"

void usage (){
	printf("LZW correct usage : lzw [-d / -c] [fileName]\n");
}

void usageRle (){
	printf("RLE correct usage : lzw [-dr / -cr] [fileName]\n");
}

void usageCompression (){
	printf("correct usage : lzw [-c] [fileName] [archiveName]\n");
}

void usageCompressionRle (){
	printf("correct usage for RLE compression : lzw [-cr] [fileName] [archiveName]\n");
}

void usageDecompression (){
	printf("correct usage : lzw [–d] [archiveName]\n");
}

void usageDecompressionRle (){
	printf("correct usage for RLE decompression : lzw [–dr] [archiveName]\n");
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

void unknownArg(char* argv){
	printf("Unknow argument %s\n", argv);
	usage();
	printf("or\n");
	usageRle();
}

int main (int argc, char **argv){
	/* -c/-d nomfichier */
	if (argc < 2){
		usage();
		return -1;
	}
	char tiret = argv[1][0];
	char operation = argv[1][1];
	char operation2 = argv[1][2];
	FILE *file; 
	FILE *file2;
	if ((tiret=='-' && operation=='c') /*|| (tiret=='-' && operation=='c' && operation2=='l')*/  && (argc != 4 && argc != 3)){
		usageCompression();
		return -1;
	}
	if ((tiret=='-' && operation=='c' && operation2=='r') && (argc != 4 && argc != 3)){
		usageCompressionRle();
		return -1;
	}
	if (tiret=='-' && operation=='d' && (argc != 4 && argc != 3)){
		usageDecompression();
		return -1;
	}
	if ((tiret=='-' && operation=='d' && operation2=='r') && (argc != 4 && argc != 3)){
		usageDecompressionRle();
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
			if (argc<4){
				usageCompression();
				return -1;
			}
			fullEncapsulate(&file, &file2, argv[2], argv[3]);
			if(!file || !file2){
		        fprintf(stderr, "Error : File error / inaccessible.\n");
		        return -1;
		    }
			if (operation2 == 'r'){
				printf("RLE encoding ...\n");
				run_length_encode(file , file2);
				printf("End\n");
			}else if (!operation2){
				printf("LZW encoding ...\n");
				compress(file, file2);
				printf("End\n");
			}else{
				unknownArg(argv[1]);
			}
			break;
		case 'd' :
			/*
			Decompression treatment
			*/
			if (argc < 3){
				usageDecompression();
				return -1;
			}
			if (strstr(argv[2], ".lzw") != NULL) {
				fullDesencapsulate(&file, &file2, argv[2]);
				if(!file || !file2){
			        fprintf(stderr, "Error : File error / inaccessible.\n");
			        return 1;
			    }
			    if (operation2 == 'r'){
			    	printf("Running RLE decompression ...\n");
			    	run_length_decode(file, file2);
			    	printf("End\n");
			    }else if(!operation2){
		    		printf("Running LZW decompression ...\n");
		    		decompress(file, file2);
		    		printf("End\n");
		    	}else{
		    		unknownArg(argv[1]);
		    	}
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