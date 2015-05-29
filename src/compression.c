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

    // tmp = w.c
    tmp = NULL;
    copySequence(w, &tmp);
    tmp = add_to_tail(tmp, c);
    printf("w.c vaut : "); print_sequence(tmp); printf("\n");

    // if w as not already been found
    /*if(treePred != NULL)
      treePred = est_dans_dico(add_to_tail(NULL, c), treePred);
    else{*/
      treePred = isPresentEncode(tmp, Dictionary);
//    }

    printf("%d\n", treePred);
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
  printf("Nombre d'éléments dans le dico : %d\n", numberElemDic(Dictionary));
}

void decompress(FILE *fr, FILE *fw){
  /*nBitsCode = 9;

  uint16_t c, toWrite;
  pSequence w = NULL;

  c = readBin(fr, nBitsCode);
  writeBin(fw, c, nBitsCode, 0);

  w = add_to_tail(NULL, c);
  while(!feof(fr) && c != eof){
    c = readBin(fr, nBitsCode);

    if(c == increment)
      nBitsCode++;
    else if(c == clean_dic){
      nBitsCode = 9;
      // vider le dico
    }
    else{
      if(c <= 255)
        toWrite = c;
      else{
        if(isPresentEncode(add_to_tail(NULL, c), Dictionary))
          writeBin(fw, /*chercher la sequence associé a c*//*, 0);
        else
          toWrite = /* w + w[0] */
      /*}
      writeBin(fw, nBitsCode, 0);
    }
  }


  /*lecture d'un caractère c;
   écrire c; // ajout à la suite d'un oubli
   w = c;
   tant que (lecture d'un caractère c) faire
       si (c > 255 && l'index c existe dans le dictionnaire) faire
           entrée = l'entrée du dictionnaire de c;
       sinon si (c > 255 && l'index c n'existe pas dans le dictionnaire) faire
           entrée = w + w[0];
       sinon
           entrée = c;
       fin si;
       sortie : écrire entrée;
       ajouter w+entrée[0] au dictionnaire;
       w = entrée;
   fin tant que;*/
}