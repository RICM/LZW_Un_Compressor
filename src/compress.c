#include "compress.h"

/*
w = Nul;
   tant que (lecture d'un caractère c) faire
       si (w + c existe dans le dictionnaire) alors
           w = w + c;
       sinon
           ajouter w + c au dictionnaire;
           écrire le code de w;
           w = c;
       fin si
   fin tant que
   écrire le code de w;
*/