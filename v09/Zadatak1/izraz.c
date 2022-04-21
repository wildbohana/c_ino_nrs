#include "izraz.h"
#include <stdio.h>

void ispisNiz(char* buffer) {
	int n = *((int*) buffer);
	int i;
	izraz *niz = (izraz*)(buffer + sizeof(int));

	for(i = 0; i < n; i++)
		printf("%d %c %d = %d\n", niz[i].broj1, niz[i].op, niz[i].broj2, niz[i].rezultat);
};

char* napraviNiz() {
	char* rez = (char*) malloc(4 * sizeof(izraz) + sizeof(int));
	izraz* niz = (izraz*) (rez + sizeof(int));

	*((int*) rez) = 4;

	niz[0] = (izraz) {11, '+', 4, 0};
	niz[1] = (izraz) {11, '-', 4, 0};
	niz[2] = (izraz) {11, '*', 4, 0};
	niz[3] = (izraz) {11, '/', 4, 0};
	
	return rez;
};
