#include <stdio.h>
#include <stdlib.h>

#include "encapsulate.h"

int main (int argc, char **argv){

	FILE *filer;
	FILE *filew;
	FILE *filew2;
	FILE *filew3;

	/*encapsulate(&filer, &filew, argv[1], argv[2]);
	fclose(filer);
	fclose(filew);


	desencapsulate(&filew2, &filew3, argv[3], argv[4]);
	fclose(filew2);
	fclose(filew3);*/

	/*fullEncapsulate(&filer, &filew, argv[1], argv[2]);
	fclose(filer);
	fclose(filew);*/

	fullDesencapsulate(&filew2, &filew3, argv[1]);
	fclose(filew2);
	fclose(filew3);

	return 0;

}