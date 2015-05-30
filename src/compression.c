#include "compression.h"

int nBitsCode = 9;

void compress(FILE *fr, FILE *fw){
  pSequence w = NULL;
  pTree treePred = NULL; 
  pTree test = NULL;
  pSequence tmp;
  uint8_t c, pred = NULL;

  initVar();

  while(!binEOF() && !feof(fr)){

    // read a new character
    c = readBin(fr, 8);

    //printf("Caractere lu : \t%c\n", c);

    if(c != 255){

      // tmp = w.c
      tmp = NULL;
      copySequence(w, &tmp);
      tmp = add_to_tail(tmp, c);
      //printf("w.c vaut : "); print_sequence(tmp); printf("\n");

      // if w as not already been found
      if(treePred != NULL && pred != NULL)
        treePred = est_dans_dico(add_to_tail(add_to_tail(NULL, pred), c), treePred);
      else{
        treePred = isPresentEncode(tmp, Dictionary);
      }

      //printf("%d\n", treePred);
      if(treePred != NULL || w == NULL){ // w.c est present dans le dictionnaire
        w = tmp;
        //printf("On a trouvé le caractere : "); print_sequence(w); printf("\n\n");
      }
      else{
        //printf("W vaut : "); print_sequence(w); printf("\n");

        printf("To add : "); print_sequence(tmp); printf("\n");
        test = add_to_dictionary(tmp, Dictionary);
        printf("prout\n");

        incrementNbits(nextCode-1, fw);
        
        if (test !=NULL){
          printf("On a inséré dans le dico : %d | %d\n",test->ascii,test->code);
        }

        if(w->succ == NULL){
          writeBin(fw, w->elem, nBitsCode, 0);
          printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
          printf("On ecrit : \t\t\t%d\n", w->elem);
        }
        else{
          writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
          printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
          printf("On ecrit : \t\t\t%d\n", isPresentEncode(w, Dictionary)->code);
        }

        w = add_to_tail(NULL, c);
        treePred = NULL;
        //printf("\n");
      }
      pred = c;

      if(nextCode == 4096){
        // dictionary reset
        nBitsCode = 9;
        writeBin(fw, clean_dic, nBitsCode, 0);
        freeDictionary(Dictionary);
        initVar();
      }
    }
  }
  printf("\tFin de fichier :\n");
  //printf("W vaut : "); print_sequence(w); printf("\n");
  if(w->succ == NULL){
    writeBin(fw, w->elem, nBitsCode, 0);
    //printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
    printf("On ecrit : \t\t\t%d\n", w->elem);
  }
  else{
    writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
    //printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
    printf("On ecrit : \t\t\t%d\n", isPresentEncode(w, Dictionary)->code);
  }

  // write the new end of file character
  writeBin(fw, eof, nBitsCode, 1);
  printf("Nombre d'éléments dans le dico : %d\n", numberElemDic(Dictionary));
  freeDictionary(Dictionary);
}

void decompress(FILE *fr, FILE *fw){
  nBitsCode = 9;
  initVar();

  uint16_t c;
  pSequence toWrite, w, seqTmp;

  c = readBin(fr, nBitsCode);
  writeBin(fw, c, 8, 0);

  printf("Caractere lu : \t%d\n", c);
  printf("Caractere ecrit : \t\t%c\n", c);

  w = add_to_tail(NULL, c);
  while(!feof(fr) && c != eof){
    printf("\n\n\n");
    c = readBin(fr, nBitsCode);
    printf("Caractere lu : \t%d\n", c);

    if(c == increment)
      nBitsCode++;
    else if(c == clean_dic){
      // dictionary reset
      nBitsCode = 9;
      freeDictionary(Dictionary);
      initVar();
    }
    else if(c != eof){
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
      
      // write the sequence toWrite
      seqTmp = toWrite;
      while(seqTmp != NULL){
        printf("Caractere ecrit : \t\t%c\n", seqTmp->elem);
        writeBin(fw, seqTmp->elem, 8, 0);
        seqTmp = seqTmp->succ;
      }

      // add w + toWrite[0] to the Dictionary
      pSequence toAdd = add_to_tail(w, toWrite->elem);
      printf("Sequence à ajouter : "); print_sequence_char(toAdd); printf(" avec comme num : %d\n", nextCode);
      add_to_dictionary(toAdd, Dictionary);

      w = toWrite;
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
    writeBin(fw, increment, nBitsCode, 0);
  }
  //printf("I = %d\n", i);
}