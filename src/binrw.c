
#include "binrw.h"

uint8_t buf = 0;
uint8_t nBitsUtil = 0;

uint16_t readBin(FILE *f, uint8_t nBits){	
	uint8_t buf_tmp, mask;
	uint16_t out;

	uint8_t nBitsToAdd = nBits;

	buf_tmp = fgetc(f);

	if(nBits == 8){
		out = buf;
		buf = buf_tmp;
	}
	else{
		mask = 0;
		for(int i=0; i<(8-nBitsUtil); i++)
			buf &= 1 << i;
		nBitsToAdd -= (8-nBitsUtil);
		for(int i=0; i<nBitsToAdd; i++)
			mask |= 1 << i;

		out = buf << nBitsToAdd;
		out |= (mask & buf_tmp) << (16-nBitsUtil);

		if(nBits - nBitsUtil - 8 > 0){

		} 
	}
	buf = buf_tmp;
	return out;
}

/** Display a split binary representation of n. */
void displayBinary(uint16_t n){
	char tmp[16];
	char s[16 + (16/4) + 1];
	int i, j;

	for(int i=0; i<16; i++)
		tmp[i] = '0';

	i =0;
	j = 0;
	while (n) {
    	if (n & 1)
        	tmp[16-1-i] = '1';
    	n >>= 1;
    	i++;
	}

	for(i=0; i<16; i++){
		if(SIZE == 16 && (i == 1 || (i-1)%(5) == 0)){
			s[j] = '-';
			j++;
		}
		s[j] = tmp[i];
		j++;
	}
	s[16 + (16/4)] = '\0';
	printf("%s\n", s);
}