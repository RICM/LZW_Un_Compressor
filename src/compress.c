#include "compress.h"

void compress(){
  pSequence w = NULL;
  pSequence tmp;
  uint8_t c;

  while(/*lecture de c*/){
    tmp = add_to_tail(w, c);
    if(isPresentEncode(tmp) && w != NULL)
      w = tmp;
    else{
      add_to_dictionary(d, tmp);
      // write w
      w = add_to_tail(NULL, c);
    }
  }
  // write w
}