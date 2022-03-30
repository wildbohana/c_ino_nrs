#include <stdio.h>
#include "BitsBuffer.h"

int next(int x){
	return (x%bitsize);
}

void initbuff(bitbuffer *b) {
	b->count = 0;
	b->first = -1;
	b->last = -1;
}

int isEmpty(bitbuffer b) {
    return b.count == 0;
}

int isFull(bitbuffer b) {
    return b.count == bitsize;
}

void setBit(char *ch, int bitindex, int num) {
	int mask = 0x80 >> bitindex;
	if (num == 0) {
		*ch = (*ch) & ~mask;
	} else {
		*ch = (*ch) | mask;
	}
}

int isSetBit(char ch, int bitindex) {
	int mask = 0x80 >> bitindex;
	return (ch & mask) != 0;
}

void push(bitbuffer *b, int num){
	if (b->count == bitsize) {
		printf("Buffer full!!!\n");
		return;
	} else if (b->count == 0) {
		b->first = 0;
		b->last = 0;
	} else {
		b->last++;
	}

	b->count++;

	int index = b->last;
	index = index >> 3; 		// deljenje sa 8

	int bitindex = b->last;
	bitindex = bitindex & 0x07;	// ostatak pri deljenju sa 9

	setBit(&b->buffer[index], bitindex, num);
}

int pop(bitbuffer *b){
	if (b->count == 0) {
		printf("Buffer empty!!!\n");
		return 0;
	}

	int index = b->first;
	index = index >> 3;

	int bitindex = b->first % 8;
	bitindex = bitindex & 0x07;

	int bit = isSetBit(b->buffer[index], bitindex);

	b->count--;
	
	if (b->count == 0) {
		b->first = 0;
		b->last = 0;
	} else
		b->first++;
	return bit;
}
