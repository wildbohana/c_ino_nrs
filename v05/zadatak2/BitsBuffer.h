#ifndef BITSBUFFER_H_INCLUDED
#define BITSBUFFER_H_INCLUDED

#define size 1024
#define bitsize 8*size

typedef struct {
    char buffer[size];
    int count, first, last;
} bitbuffer;

void initbuff(bitbuffer *b);

int isEmpty(bitbuffer b);

int isFull(bitbuffer b);

void setBit(char *ch, int bitindex, int num);

int isSetBit(char ch, int bitindex);

void push(bitbuffer *b, int num);

int pop(bitbuffer *b);

#endif
