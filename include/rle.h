#ifndef _RLE_H
#define _RLE_H

/* procedure qui realise l'encodage RLE */
void run_length_encode(FILE *in , FILE *out);

/* procedure qui realise le decodage RLE */
void run_length_decode(FILE *in , FILE *out);

#endif