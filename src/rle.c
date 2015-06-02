#include <stdio.h>
#include <limits.h>

void run_length_encode(FILE *in , FILE *out) {

	int current_char, prev_char; /* caracteres courant et precedent */
	unsigned char count; /* nombre de caracteres en serie */

	prev_char = EOF;
	count = 0;

	/* lire du fichier */
	while((current_char = fgetc(in)) != EOF) {
		fputc(current_char, out);

		/* verifier s'il y a repetition */
		if(current_char == prev_char) {
			/* on a une serie de caracteres, faut compter le nombre de repetitions */
			count = 0;

			while((current_char = fgetc(in)) != EOF) {
				if(current_char == prev_char) {
					count++;

					if(count == UCHAR_MAX) {
						/* compter tant que possible */
						fputc(count, out);

						/* forcer le caractere suivant a etre different */
						prev_char = EOF;
						break;
					}
				} else {
					/* la serie est terminee */
					fputc(count, out);
					fputc(current_char, out);
					prev_char = current_char;
					break;
				}
			}
		} else {
			/* pas de serie */
			prev_char = current_char;
		}

		if(current_char == EOF) {
			/* la serie est terminee a cause de EOF */
			fputc(count, out);
			break;
		}
	}
}

void run_length_decode(FILE *in , FILE *out) {
	int current_char, prev_char;
	unsigned char count;

	prev_char = EOF;

	while((current_char = fgetc(in)) != EOF) {
		
		fputc(current_char, out);

		/* verifier s'il y a une repetition */
		if(current_char == prev_char) {
			/* il y a repetition */
			count = fgetc(in);
			while(count > 0) {
				fputc(current_char, out);
				count--;
			}

			prev_char = EOF; /* forcer le caractere suivant a etre different */
		} else {
			/* pas de repetition */
			prev_char = current_char;
		}
	}
}