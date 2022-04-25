#ifndef IZRAZ_H_INCLUDED
#define IZRAZ_H_INCLUDED

typedef struct {
    short broj1;
    char op;
    short broj2;
    int rezultat;
} izraz;

void ispisNiz(char* buffer);

char* napraviNiz();

#endif
