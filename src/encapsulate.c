#include "encapsulate.h"

//Put the extension of the original file at the beginning of the compressed one.
void encapsulate(FILE **fr, FILE ** fw, char* fileName, char* fileNameOut){
	//Opening of the input file.
	*fr = fopen(fileName,"rb");

	//Searching file extension
	char exte[10] = {'0'};
	int j = 0;
	int l = strlen(fileName);
	int ok =1;

	while(l >= 0 && j<10 && ok){
		if (*(fileName+l) == '.')
		{
			ok = 0;
		}
		else {
			exte[j] = *(fileName+l);
			l--;
			j++;
		}
	}

	char tmp[100];
	memcpy(tmp,fileNameOut,strlen(fileNameOut));
	strncat(tmp,".lzw",strlen(fileNameOut)+4);
	*fw = fopen(tmp,"wb");

	if (l == 0 || j ==10)
	{
		printf("Pas d'extension.\n");
	}
	else {
		//Insertion of the extension at the beginning of the compressed file
		j=0;
		for (j = 0; j < 10; ++j)
		{
			if (exte[j] != 0)
			{
				writeBin(*fw,exte[j],8,0);
			}
		}
		writeBin(*fw,255,8,0);
	}
}

//Read the extension of the original file at the beginning of the compressed file and create the correct file.
void desencapsulate(FILE **fr, FILE ** fw, char* fileName, char* fileNameOut){
	uint8_t extep;
	char exte[11];
	int j = 0;
	*fr = fopen(fileName,"rb");
	//Reading of the extension
	extep = readBin(*fr, 8);
	while(extep != 255 && j < 10){
		exte[j] = extep;
		j++;
		extep = readBin(*fr, 8);
	}
	exte[j] = '\0';
	char tmp[100];
	memcpy(tmp,fileNameOut,strlen(fileNameOut));
	tmp[strlen(fileNameOut)] = '\0';
	strncat(tmp,".",strlen(tmp)+1);
	strncat(tmp,exte,strlen(tmp)+strlen(exte));
	*fw = fopen(tmp,"wb");
}

//Encapsulate the entirety of the orginal file name at the beginning of the compressed file.
void fullEncapsulate(FILE **fr, FILE ** fw, char* fileName, char* fileNameOut){
	//Opening of the input file
	*fr = fopen(fileName,"rb");

	//Opening of the output file
	char tmp[100];
	memcpy(tmp,fileNameOut,strlen(fileNameOut));
	strncat(tmp,".lzw",strlen(fileNameOut)+4);
	*fw = fopen(tmp,"wb");
	for (int i = 0; i < strlen(fileName); ++i)
	{
		writeBin(*fw,*(fileName+i),8,0);
	}
	writeBin(*fw,255,8,0);
}

//Read the original name of the compressed file and recreate it.
void fullDesencapsulate(FILE **fr, FILE ** fw, char* fileName){
	*fr = fopen(fileName,"rb");
	char tmp[101];
	uint8_t octo;
	int j = 0;
	do {
		octo = readBin(*fr, 8);
		//printf("octo: %c\n", octo);
		tmp[j] = octo;
		j++;
	} 
	while (octo != 255 && j < 100 );

	tmp[j-1] = '\0';
	for (int i = 0; i < strlen(tmp); ++i)
	{
		//printf("%c\n", tmp[i]);
	}

	*fw = fopen(tmp,"wb");
}