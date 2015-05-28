
#include "binrw.h"

Buffer buf;
Buffer bufW;
uint8_t eof = 0;
uint8_t first = 1;

void initBuffer(){
	buf.data = 0;
	buf.remain = 0;

	bufW.data = 0;
	bufW.remain = 0;
}

uint16_t readBin(FILE *f, uint8_t nBits){	
	Buffer buf_tmp;
	uint8_t mask;
	uint16_t out;

	// bits remaining to add	
	int nBitsRemaining = nBits;

	// initialise temporary buffer
	buf_tmp.data = fgetc(f);
	buf_tmp.remain = 8;

	//printf("Buffer local : \n\t"); displayBinary(buf.data);
	//printf("Buffer courrant : \n\t"); displayBinary(buf_tmp.data);

	// for encoding
	if(nBits == 8){
		buf.data = buf_tmp.data;
		out = buf.data;
	}// for decoding
	else{

		// add the non-used bits inside the buffer
		mask = 0;
		for(int i=0; i<buf.remain; i++)
			mask |= 1 << i;

		out = (buf.data & mask) << (nBits-buf.remain);
		//printf("Ecriture avec buffer pred : \n\t"); displayBinary(out);

		// add bits from current buffer
		nBitsRemaining -= buf.remain;

		if(nBitsRemaining < 8){
			out |= buf_tmp.data >> (8-nBitsRemaining);
			buf.remain = 8-nBitsRemaining;
		}
		else{
			out |= buf_tmp.data << (nBits-buf.remain-8);

			nBitsRemaining -= 8;

			// we have to read another octet
			if(!feof(f) && nBitsRemaining > 0){
				buf_tmp.data = fgetc(f);
				out |= buf_tmp.data >> (8-nBitsRemaining);
				buf.remain = 8-nBitsRemaining;
			}
			else if(feof(f))
				eof = 1;
			else{
				buf_tmp.data = fgetc(f);
				buf.remain = nBitsRemaining;
			}
		}
		//printf("Ecriture avec nouveau buffer : \n\t"); displayBinary(out);
		//printf("Buf remain : %d\n", buf.remain);
	}
	buf.data = buf_tmp.data;
	return out;
}

void writeBin(FILE *f, uint16_t toWrite, uint8_t nBits, uint8_t isFinal){
	printf("Write !\n");
	Buffer bufW_tmp;
	uint8_t write_tmp;

	// for decoding
	if(nBits == 8){
		bufW.data = toWrite;
		bufW.remain = 0;
		displayBinary(toWrite);
		fputc(toWrite, f);
	}// for encoding
	else{
		printf("Buffer pred : "); displayBinary(bufW.data);
		bufW_tmp.data = toWrite;
		bufW_tmp.remain = nBits;
		printf("New buffer : "); displayBinary(bufW_tmp.data);

		write_tmp = 0;

		// ecriture de ce qu'il y a dans le buffer précédent
		write_tmp |= bufW.data << (8-bufW.remain) | bufW_tmp.data >> (nBits-(8-bufW.remain));
		bufW_tmp.remain = bufW_tmp.remain - (8-bufW.remain);
		printf("Remain : %d\n", bufW_tmp.remain);
		printf("A afficher : ");displayBinary(write_tmp);

		while(bufW_tmp.remain >= 8){
			write_tmp = 0;
			write_tmp |= bufW_tmp.data >> (8-bufW_tmp.remain);
			bufW_tmp.remain -= 8;
			printf("Remain : %d\n", bufW_tmp.remain);
			printf("A afficher : ");displayBinary(write_tmp);
		}

		bufW.data = 0;
		bufW.remain = 0;

		if(isFinal){
			while(bufW.remain > 0){
				write_tmp = 0;
				// assemble previous buffer to new
				write_tmp |= bufW.data << (8-bufW.remain);

				printf("Remain : %d\n", bufW.remain);
				printf("A afficher : ");displayBinary(write_tmp);
			}
		}
		bufW.data = bufW_tmp.data;
		bufW.remain = bufW_tmp.remain;
	}
}

uint8_t binEOF(){
	return eof;
}

/** Display a split binary representation of n. */
void displayBinary(uint16_t n){
	char tmp[16];
	char s[20];
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
		if(i%4 == 0 && i!=0){
			s[j] = '-';
			j++;
		}
		s[j] = tmp[i];
		j++;
	}
	s[19] = '\0';
	printf("%s\n", s);
}