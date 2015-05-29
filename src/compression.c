#include "compression.h"

int nBitsCode = 9;

void compress(FILE *fr, FILE *fw){
  pSequence w = NULL;
  pTree treePred = NULL; 
  pTree test = NULL;
  pSequence tmp;
  uint8_t c;

  InitVar();

  while(!binEOF() && !feof(fr)){

    // read a new c
    c = readBin(fr, 8);

    printf("Caractere lu : \t%c\n", c);

    if(c == increment){
      nBitsCode++;
    }
    else{

      // tmp = w.c
      tmp = NULL;
      copySequence(w, &tmp);
      tmp = add_to_tail(tmp, c);
      printf("w.c vaut : "); print_sequence(tmp); printf("\n");

      // if w as not already been found
      if(treePred != NULL)
        treePred = est_dans_dico(add_to_tail(NULL, c), treePred);
      else{
        treePred = isPresentEncode(tmp, Dictionary);
      }

      if(treePred != NULL || w == NULL){ // w.c est present dans le dictionnaire
        w = tmp;
        printf("On a trouvé le caractere : "); print_sequence(w); printf("\n\n");
      }
      else{
        printf("W vaut : "); print_sequence(w); printf("\n");

        printf("To add : "); print_sequence(tmp); printf("\n");
        test = add_to_dictionary(tmp, Dictionary);

        printf("Debug\n");
        
        if (test !=NULL){
          printf("On a inséré dans le dico : %d | %d\n",test->ascii,test->code);
        }

        if(w->succ == NULL){
          writeBin(fw, w->elem, nBitsCode, 0);
          printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
          printf("On ecrit : %c\n", w->elem);
        }
        else{
          writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
          printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
          printf("On ecrit : %d\n", isPresentEncode(w, Dictionary)->code);
        }

        // write w
        /*if(w != NULL && w->succ != NULL){
          writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
          printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
          printf("On ecrit : %d\n", isPresentEncode(w, Dictionary)->code);
        }
        else{
          writeBin(fw, c, nBitsCode, 0);
          printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
          printf("On ecrit : %c\n", c);
        }*/


        w = add_to_tail(NULL, c);
        treePred = NULL;

        printf("GOES TO NEXT\n\n");
      }
    }
  }
  printf("Fin de fichier\n");
  printf("W vaut : "); print_sequence(w); printf("\n");
  if(w->succ == NULL){
    writeBin(fw, w->elem, nBitsCode, 0);
    printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
    printf("On ecrit : %d\n", w->elem);
  }
  else{
    writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
    printf("W vaut apres insertion : "); print_sequence(w); printf("\n");
    printf("On ecrit : %d\n", isPresentEncode(w, Dictionary)->code);
  }
  writeBin(fw, eof, nBitsCode, 1);
}

void decompress(FILE *fr, FILE *fw){
  
}