
#include "binrw.h"

Buffer buf, bufPred;
Buffer bufW;
uint8_t end_of_file = 0;

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

	if(DEBUG_BINRW_LEVEL == 2){
		printf("Number of bit remaining: \t\t%d\n", buf.remain);
		printf("Local buffer: \t\t\t"); displayBinary(buf.data, 2); printf("\n");
		printf("Current buffer: \t\t"); displayBinary(buf_tmp.data, 2); printf("\n");
	}

	bufPred.data = buf.data;
	bufPred.remain = buf.remain;

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
		if(DEBUG_BINRW_LEVEL == 2){
			printf("First phase - old buffer: \t"); displayBinary(out, 2); printf("\n");
		}

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

				if(DEBUG_BINRW_LEVEL == 2){
					printf("New buffer: \t\t\t"); displayBinary(buf_tmp.data, 2); printf("\n");
				}

				out |= buf_tmp.data >> (8-nBitsRemaining);
				buf.remain = (8-nBitsRemaining == 0)? 8 : 8-nBitsRemaining;
			}
			else if(feof(f))
				end_of_file = 1;
			else{
				buf_tmp.data = fgetc(f);
				if(DEBUG_BINRW_LEVEL == 2){
					printf("New buffer: \t\t\t"); displayBinary(buf_tmp.data, 2); printf("\n");
				}
				buf.remain = (nBitsRemaining == 0)? 8 : nBitsRemaining;
			}
		}
		
		if(DEBUG_BINRW_LEVEL == 2){
			printf("Second phase - new buffer: \t"); displayBinary(out, 2); printf("\n");
			printf("Nbits remainaing : \t%d\n", buf.remain);
		}
		#if DEBUG_BINRW_LEVEL == 1 || DEBUG_BINRW_LEVEL == 2
			printf("Out: \t\t\t\t"); displayBinary(out, 2); printf("\n");
			printf("\n");
		#endif
	}
	buf.data = buf_tmp.data;
	return out;
}

void writeBin(FILE *f, uint16_t toWrite, uint8_t nBits, uint8_t isFinal){
	Buffer bufW_tmp;
	uint8_t write_tmp;

	// for decoding
	if(nBits == 8){
		bufW.data = toWrite;
		bufW.remain = 0;
		#if DEBUG_BINRW_LEVEL == 1 || DEBUG_BINRW_LEVEL == 2
			printf("To print: \t\t\t"); displayBinary(toWrite, 1); printf("\n");
		#endif
		fputc(toWrite, f);
	}// for encoding
	else{

		bufW_tmp.data = toWrite;
		bufW_tmp.remain = nBits;
		
		if(DEBUG_BINRW_LEVEL == 2){
			printf("Buffer pred : \t\t\t"); displayBinary(bufW.data, 2); printf("\n");
			printf("New buffer : \t\t\t"); displayBinary(bufW_tmp.data, 2); printf("\n");
		}

		write_tmp = 0;

		// ecriture de ce qu'il y a dans le buffer précédent
		write_tmp |= bufW.data << (8-bufW.remain) | bufW_tmp.data >> (nBits-(8-bufW.remain));
		bufW_tmp.remain = bufW_tmp.remain - (8-bufW.remain);

		if(DEBUG_BINRW_LEVEL == 2)
			printf("Remain: \t\t%d\n", bufW_tmp.remain);
		#if DEBUG_BINRW_LEVEL == 1 || DEBUG_BINRW_LEVEL == 2
			printf("To print: \t\t\t");displayBinary(write_tmp, 1); printf("\n");
		#endif

		fputc(write_tmp, f);
		

		while(bufW_tmp.remain >= 8){
			write_tmp = 0;
			write_tmp |= bufW_tmp.data >> (bufW_tmp.remain-8);
			bufW_tmp.remain -= 8;

			if(DEBUG_BINRW_LEVEL == 2)
				printf("Remain : \t\t%d\n", bufW_tmp.remain);
			#if DEBUG_BINRW_LEVEL == 1 || DEBUG_BINRW_LEVEL == 2
				printf("To print: \t\t\t");displayBinary(write_tmp, 1); printf("\n");
			#endif

			fputc(write_tmp, f);
		}

		if(isFinal){
			if(bufW_tmp.remain > 0){
				write_tmp = 0;
				// assemble previous buffer to new
				write_tmp |= bufW_tmp.data << (8-bufW_tmp.remain);
				bufW_tmp.remain = 0;

				if(DEBUG_BINRW_LEVEL == 2)
					printf("Remain: \t\t%d\n", bufW_tmp.remain);
				#if DEBUG_BINRW_LEVEL == 1 || DEBUG_BINRW_LEVEL == 2
					printf("To print: \t\t\t");displayBinary(write_tmp, 1); printf("\n");
				#endif

				fputc(write_tmp, f);
			}
		}

		#if DEBUG_BINRW_LEVEL == 1 || DEBUG_BINRW_LEVEL == 2
			printf("\n");
		#endif		

		bufW.data = bufW_tmp.data;
		bufW.remain = bufW_tmp.remain;
	}
}

uint8_t binEOF(){
	return end_of_file;
}

/** Display a split binary representation of n. */
void displayBinary(uint16_t n, uint8_t nOctets){
	char tmp[8*(nOctets)];
	char s[10*(nOctets)];
	int i, j;

	for(int i=0; i<8*nOctets; i++)
		tmp[i] = '0';

	i =0;
	j = 0;
	while (n) {
    	if (n & 1)
        	tmp[8*nOctets-1-i] = '1';
    	n >>= 1;
    	i++;
	}

	for(i=0; i<8*nOctets; i++){
		if(i%4 == 0 && i!=0){
			if(nOctets == 2 && i == 8)
				s[j] = ' ';
			else
				s[j] = '-';
			j++;
		}
		s[j] = tmp[i];
		j++;
	}
	s[10*nOctets-1] = '\0';
	printf("%s", s);
}

uint8_t emptyReadBuffer(){
	return buf.data == 0 && buf.remain == 0;
}

uint8_t emptyWriteBuffer(){
	return bufW.data == 0 && bufW.remain == 0;
}

uint16_t readLast(uint8_t nBits){
	uint8_t mask = 0;
	for(int i=0; i<8; i++)
		mask |= 1 << i;

	uint16_t out = buf.data;
	uint8_t remain = buf.remain;
	buf.data = 0;
	buf.remain = 0;
	return out /*<< (nBits-remain)*/;
}

void printBufferRead(){
	displayBinary(buf.data, 2); 
	printf("   Remain : %d\n", buf.remain);
}

void printBufferReadPred(){
	displayBinary(bufPred.data, 2); 
	printf("   Remain : %d\n", bufPred.remain);
}

void flushBufferRead(){
	buf.data = 0;
	buf.remain = 0;
}