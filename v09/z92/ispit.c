#include <stdio.h>
#include "ispit.h"

void ispisiPodatke(char* buffer)
{
	int brSt = *((int*) buffer);
	int brPr = *((int*) (buffer + sizeof(int)));
	ispit* is = (ispit*) (buffer + 2 * sizeof(int));

	printf("Ispis podataka o ispitima:\n");
	printf("Broj studenata: %d\n", brSt);
	printf("Broj predmeta: %d\n", brPr);

	for(int j = 0; j < brPr; j++)
		for(int i = 0; i < brSt; i++)
			printf("%hd.%hd.%hd %c %d %s\n",
				is[j * brSt + i].dan,
				is[j * brSt + i].mesec,
				is[j * brSt + i].godina,
				is[j * brSt + i].ocena,
				is[j * brSt + i].sifraIspRok,
				is[j * brSt + i].profesor);
};
