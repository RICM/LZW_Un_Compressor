#include "compression.h"

int nBitsCode;

/** 
  Compress a file indicated by fr into 
  another file indicated by fw 
*/
void compress(FILE *fr, FILE *fw){
  pSequence w = NULL;
  pSequence tmp;
  pTree treePred = NULL;

  int isInside;

  // Current character
  uint8_t c;

  // Previous character
  int pred = -1;

  // Boolean to indicate if previous sequence has been found or not
  int found = 0;

  // Initialisation of the variables
  nBitsCode = 9;
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

      if(found) // if w as not already been found
        isInside = isPresentInTree(add_to_tail(add_to_tail(NULL, pred), c), treePred, &treePred);
      else
        isInside = isPresentInDico(tmp, Dictionary, &treePred);

      if(isInside != -1 || w == NULL){ // w.c is in the dictionary
        // free w
        freeSequenceList(&w);

        // w = tmp = w.c by copy
        w = NULL;
        copySequence(tmp, &w);
        w = tmp;

        found = 1;
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

          writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
          if(DEBUG_COMPRESSION_LEVEL == 2)
            printf("%d\n", isPresentEncode(w, Dictionary)->code);
        }

        // w = c
        w = add_to_tail(NULL, c);
        // reinit treePred
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
      freeDictionary(Dictionary);
      initVar();
      freeSequenceList(&w);
      pred = -1;
      treePred = NULL;
      tmp = NULL;
      found = 0;
      nBitsCode = 9;
    }
  }
  // second to last character to write
  if(w->succ == NULL){
    writeBin(fw, w->elem, nBitsCode, 0);
    //printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
    //printf("On ecrit : \t\t\t%d\n", w->elem);
  }
  else{
    writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
    //printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
    //printf("On ecrit : \t\t\t%d\n", isPresentEncode(w, Dictionary)->code);
  }

  // write the new end of file character
  writeBin(fw, eof, nBitsCode, 1);
  freeDictionary(Dictionary);
}

void decompress(FILE *fr, FILE *fw){
  nBitsCode = 9;
  initVar();
  pSequence toAdd;

  uint16_t c;
  pSequence toWrite, w, seqTmp;

  c = readBin(fr, nBitsCode);
  writeBin(fw, c, 8, 0);
  //printf("%d\n", c);

  int i = 0;

  //printf("Caractere lu : \t%d\n", c);
  //printf("Caractere ecrit : \t\t%c\n", c);

  w = add_to_tail(NULL, c);
  while(!feof(fr) && c != eof){
    //printf("\n\n\n");
    c = readBin(fr, nBitsCode);

    if(c == increment)
      nBitsCode++;
    else if(c == clean_dic){
      // dictionary reset

      //printBufferReadPred();
      //printBufferRead();

      /*c = readLast(nBitsCode);
      printf("Caractere lu final : \t%d\n", c);
      writeBin(fw, c, 8, 0);*/

      freeDictionary(Dictionary);
      initVar();

      /*if(!emptyReadBuffer()){
        c = readBin(fr, nBitsCode);
        //printf("%d\n", c);
        printf("Caractere lu final : \t%d\n", c);
        writeBin(fw, c, 8, 0);
      }*/
      nBitsCode = 9;

      //flushBuffer();

      if(!feof(fr)){
        c = readBin(fr, nBitsCode);
        writeBin(fw, c, 8, 0);
        //printf("Caractere lu : \t%d\n", c);
        w = add_to_tail(NULL, c);
      }
    }
    else if(c != eof){
      //if(c == 1)
        //  printf("Coucou mon mignon !\t\t");
      //printf("Caractere lu : \t%d\n", c);
      if(c <= 255)
        toWrite = add_to_tail(NULL, c);
      else{
        toWrite = findCode(c, DecodeDictionary);
        if(toWrite == NULL){
          toWrite = NULL;
          copySequence(w, &toWrite);
          toWrite = add_to_tail(toWrite, w->elem);
        }
      }
      
      /*if(toWrite->elem == 5){
        printf("Bug : \t"); print_sequence(toWrite); printf("\n");
        getchar();
      }*/

      // write the sequence toWrite
      seqTmp = toWrite;
      //printf("Bug : \t"); print_sequence(toWrite); printf("\n");
      while(seqTmp != NULL){
        //printf("Caractere ecrit : \t\t%c\n", seqTmp->elem);
        writeBin(fw, seqTmp->elem, 8, 0);
        //if(c == 1)
          //printf("%d\n", seqTmp->elem);
        /*if(seqTmp->elem == 31){
          i++;
          if(i == 17)
            getchar();
        }*/
        seqTmp = seqTmp->succ;
      }

      // add w + toWrite[0] to the Dictionary
      toAdd = NULL;
      copySequence(w, &toAdd);
      toAdd = add_to_tail(toAdd, toWrite->elem);
      //printf("Sequence à ajouter : "); print_sequence_char(toAdd); printf(" avec comme num : %d\n", nextCode);
      add_to_dictionary(toAdd, Dictionary);

      w = NULL;
      copySequence(toWrite, &w);
    }
  }
}

void incrementNbits(uint16_t value, FILE *fw){
  uint16_t tmp = value;
  uint8_t i = 0;
  while(tmp){
    tmp >>= 1;
    i++;
  }
  if(nBitsCode < i){
    nBitsCode++;
    writeBin(fw, increment, nBitsCode-1, 0);
  }
}