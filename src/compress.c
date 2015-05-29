#include "compress.h"

int nBitsCode = 9;

void compress(FILE *fr, FILE *fw){
  pSequence w = NULL;
  pTree treePred = NULL; 
  pSequence tmp;
  uint8_t c;

  InitVar();

  while(!binEOF() && !feof(fr)){

    // read a new c
    c = readBin(fr, 8);

    if(c == increment){
      nBitsCode++;
    }
    else{
      tmp = w;
      tmp = add_to_tail(tmp, c);

      if(treePred != NULL)
        treePred = est_dans_dico(add_to_tail(NULL, c), treePred);
      else
        treePred = isPresentEncode(tmp, Dictionary);

      if(treePred != NULL)
        w = tmp;
      else{
        printf("test\n");
        print_sequence(tmp);
        printf("\n");

        add_to_dictionary(tmp, Dictionary);
        printf("blablabug %d \n", w);

        // write w
        if(w != NULL){
          pTree code = isPresentEncode(w, Dictionary);//->code;
          printf("%d\n", code->code); 
          writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 0);
        }
        else{
          writeBin(fw, c, nBitsCode, 0);
          printf("On ecrit : %d\n", c);
        }

        w = add_to_tail(NULL, c);
        treePred = NULL;
      }
    }
  }
  writeBin(fw, isPresentEncode(w, Dictionary)->code, nBitsCode, 1);
}