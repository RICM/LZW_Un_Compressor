#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "binrw.h"

void binaryRead(FILE* f, uint8_t nOctetPerLine, uint8_t nBits){
	char characters[nOctetPerLine];
	uint8_t newNOctets = nOctetPerLine;
	uint8_t nLine = 0;
	uint8_t numberOfline = 0;
	uint16_t bin; 
	int i;
	uint8_t cont = 1;
	char toRead, buf;

	while(!feof(f) && !binEOF() && cont){
		if(nLine > 255)
			nLine = 0;
		if(nLine>>4 == 0)
			printf("0");
		printf("%x  ", nLine);
		for(i=0; i<newNOctets && !feof(f); i++){
			bin = readBin(f, nBits);
			characters[i] = bin;
			if(nBits == 8)
				displayBinary(bin, 1);
			else
				displayBinary(bin, 2);
			printf(" ");
		}
		if(feof(f)){
			for(int j=i; j<newNOctets; j++)
				printf("......... ");
			newNOctets = i;
		}
		printf(" ");
		for(i=0; i<newNOctets; i++){
			if(characters[i]>31)
				printf("%c", characters[i]);
			else
				printf(".");
		}
		for(int j=i; j<nOctetPerLine; j++)
			printf(".");
		printf("\n");
		nLine += newNOctets;
		numberOfline++;

		if(numberOfline == 32){
			numberOfline = 0;
			do{
				printf("Press C to continue or Q to quit. ");
				scanf("%c", &toRead);
				buf = getchar();
			}while(toRead != 'c' && toRead != 'C' && toRead != 'q' && toRead != 'Q');
			printf("\033[F");
			if(toRead == 'q' || toRead == 'Q')
				cont = 0;
		}
	}
}

int main (int argc, char **argv){
	FILE *file;
	
	if(argc != 3){
		fprintf(stderr, "Error : ./bindump [filename] [number of bits for encoding]\n");
		return 1;
	}

	file = fopen(argv[1], "rb");
	int nBits;
	sscanf(argv[2], "%d", &nBits);
	if(nBits < 8 || nBits > 16){
		fprintf(stderr, "Error : Number of bits for encoding has to be a number between 8 and 16.\n");
		return 1;
	}

	if(!file){
        fprintf(stderr, "Error : file is inaccessible.\n");
        return 1;
    }
    else{
    	if(nBits > 8)
    		binaryRead(file, 4, nBits);
    	else
    		binaryRead(file, 8, nBits);
    	fclose(file);
    }
	return 0;
}

