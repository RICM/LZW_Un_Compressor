#ifndef _encapsulate_h
#define _encapsulate_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>

#include "binrw.h"

//Put the extension of the original file at the beginnign of the compressed one.
void encapsulate(FILE **fr, FILE ** fw, char* fileName, char* fileNameOut);

//Read the extension of the original file at the begining of the compressed file and create the correct file.
void desencapsulate(FILE **fr, FILE ** fw, char* fileName, char* fileNameOut);

//Encapsulate the entirety of the orginal file name at the beginning of the compressed file.
void fullEncapsulate(FILE **fr, FILE ** fw, char* fileName, char* fileNameOut);

//Read the original name of the compressed file and recreate it.
void fullDesencapsulate(FILE **fr, FILE ** fw, char* fileName);
#endif