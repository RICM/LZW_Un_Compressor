#include "compression.h"

int nBitsCode;
int interval;

/** 
  Compress a file indicated by fr into 
  another file indicated by fw 
*/
void compress(FILE *fr, FILE *fw){
  pSequence w = NULL, tmp = NULL, toSearch = NULL;
  pTree treeFound = NULL, treePred = NULL;

  int isInside;

  // Current character
  uint8_t c;

  // Previous character
  int pred = -1;

  // Boolean to indicate if previous sequence has been found or not
  int found = 0;

  // Initialisation of the variables
  nBitsCode = 9;
  interval = 1<<nBitsCode;
  initVar();

  // While end of file is not reached, compress
  while(!binEOF() && !feof(fr)){

    // read a new character
    c = readBin(fr, 8);

    if(!feof(fr)){

      if(DEBUG_COMPRESSION_LEVEL == 1)
        printf("%d\n", c);

      // tmp = w.c
      tmp = NULL;
      copySequence(w, &tmp);
      tmp = add_to_tail(tmp, c);

      if(found){ // if w as not already been found
        toSearch = add_to_tail(add_to_tail(NULL, pred), c);
        isInside = isPresentInTree(toSearch, treeFound, &treeFound);
        freeSequenceList(&toSearch);
      }
      else
        isInside = isPresentInDico(tmp, Dictionary, &treeFound);

      if(isInside != -1 || w == NULL){ // w.c is in the dictionary
        // free w
        freeSequenceList(&w);

        // w = tmp = w.c by copy
        w = NULL;
        copySequence(tmp, &w);
        w = tmp;

        found = 1;
        treePred = treeFound;
      }
      else{
        // w.c is not found, add it to the dictionary
        add_to_dictionary(tmp, Dictionary);

        incrementNbits(nextCode-1, fw);
        
        if(w->succ == NULL){ // if w is just a character, write the character
          writeBin(fw, w->elem, nBitsCode, 0);
          if(DEBUG_COMPRESSION_LEVEL == 2)
            printf("%d\n", w->elem);
        }
        else{
          writeBin(fw, treePred->code, nBitsCode, 0);
          if(DEBUG_COMPRESSION_LEVEL == 2)
            printf("%d\n", treePred->code);      
        }

        // w = c
        freeSequenceList(&w);
        w = add_to_tail(NULL, c);

        // reinit treeFound
        treeFound = NULL;
        treePred = NULL;
        found = 0;
      }
      pred = c;
    }

    if(nextCode == 16384){

      // dictionary reset
      c = readLast(nBitsCode);
      writeBin(fw, c, nBitsCode, 0);

      // clear the read buffer
      flushBufferRead();

      // write the character for cleaning the dictionary
      writeBin(fw, clean_dic, nBitsCode, 0);

      // reinit dictionary and variables
      freeDictionary();
      initVar();

      freeSequenceList(&w);

      pred = -1;
      treeFound = NULL;
      treePred = NULL;
      found = 0;

      nBitsCode = 9;
      interval = 1<<nBitsCode;
    }
  }

  // second to last character to write
  if(w->succ == NULL){
    writeBin(fw, w->elem, nBitsCode, 0);
    if(DEBUG_COMPRESSION_LEVEL == 2)
      printf("%d\n", w->elem);
  }
  else{
    writeBin(fw, treePred->code, nBitsCode, 0);
    if(DEBUG_COMPRESSION_LEVEL == 2)
      printf("%d\n", treePred->code);      
  }

  // write the new end of file character
  writeBin(fw, eof, nBitsCode, 1);
  if(DEBUG_COMPRESSION_LEVEL == 2)
    printf("%d\n", eof);

  freeSequenceList(&w);
  freeDictionary();
}


/** 
  Decompress a file indicated by fr into 
  another file indicated by fw 
*/
void decompress(FILE *fr, FILE *fw){

  pSequence toAdd = NULL, toWrite = NULL, w = NULL, seqTmp = NULL;  

  uint16_t c;

  // Initialisation of the variables
  nBitsCode = 9;
  initVar();

  // read the first character of the file
  c = readBin(fr, nBitsCode);
  writeBin(fw, c, 8, 0);
  if(DEBUG_COMPRESSION_LEVEL == 1 || DEBUG_COMPRESSION_LEVEL == 2)
    printf("%d\n", c);

  // w = c
  w = add_to_tail(NULL, c);
  while(!feof(fr) && c != eof){
    c = readBin(fr, nBitsCode);

    if(c == increment)
      nBitsCode++;
    else if(c == clean_dic){
      // dictionary reset
      freeDictionary();
      nBitsCode = 9;
      initVar();

      if(!feof(fr)){
        // read a new first character
        c = readBin(fr, nBitsCode);
        writeBin(fw, c, 8, 0);
        if(DEBUG_COMPRESSION_LEVEL == 1 || DEBUG_COMPRESSION_LEVEL == 2)
          printf("%d\n", c);

        // w = c
        freeSequenceList(&w);
        w = add_to_tail(NULL, c);
      }
    }
    else if(c != eof){
      if(c <= 255)
        toWrite = add_to_tail(NULL, c);
      else{
        toWrite = findCode(c, DecodeDictionary);
        // if toWrite is not found, toWrite = w.w[0]
        if(toWrite == NULL){
          copySequence(w, &toWrite);
          toWrite = add_to_tail(toWrite, w->elem);
        }
      }

      // write the sequence toWrite
      seqTmp = toWrite;
      while(seqTmp != NULL){
        writeBin(fw, seqTmp->elem, 8, 0);
        if(DEBUG_COMPRESSION_LEVEL == 1)
          printf("%d\n", seqTmp->elem);
        seqTmp = seqTmp->succ;
      }

      // add w + toWrite[0] to the Dictionary
      //freeSequenceList(&toAdd);
      toAdd = NULL;
      copySequence(w, &toAdd);
      toAdd = add_to_tail(toAdd, toWrite->elem);
      add_to_dictionary(toAdd, Dictionary);

      // copy w + toWrite[0] into w
      //w = NULL;
      freeSequenceList(&w);
      copySequence(toWrite, &w);
    }
  }

  freeSequenceList(&w);
  freeSequenceList(&toAdd);
  freeSequenceList(&toWrite);
  freeDictionary();
}

/**
  Test if a value, has to be code on more bits
  and increment nBitCode if so
*/
void incrementNbits(uint16_t value, FILE *fw){
  if(value == interval){
    nBitsCode++;
    writeBin(fw, increment, nBitsCode-1, 0);
    interval <<= 1;
  }
}