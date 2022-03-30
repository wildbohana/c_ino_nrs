#include <stdio.h>
#include <stdlib.h>

int * CalculateMinMax(char *buffer) {

	int *rez = (int *)malloc(2 * sizeof(int));
	int N = (int)(*buffer);
	int *niz = (int *)(buffer + sizeof(char));

	rez[0] = niz[0];		// min
	rez[1] = niz[0];		// max

	// prolaz kroz niz, racunanje min i max
	for (int i = 1; i < N; i++) {
		if (niz[i] < rez[0]) {
			rez[0] = niz[i];
		}
		if (niz[i] > rez[1]) {
			rez[1] = niz[i];
		}
	}

	return rez;
}


int main(int argc, char *argv[])
{
	short n;		// N>0 koji se unosi
	printf("Unesi broj N > 0: ");
	scanf_s("%hi", &n);

	printf("\n");

	int *niz = (int *)malloc(n * sizeof(int));

	printf("Unos niza:\n");
	for (int i = 0; i < n; i++) {
		printf("niz[%d] = ", i);
		scanf_s("%d", &niz[i]);
	}

	// spakovati broj N i unete brojeve u niz bajtova u buffer (koji je niz char-ova)
	char *buffer = (char *)malloc(n * sizeof(int) + sizeof(char));
	buffer[0] = (char)n;

	// pokazivač *brojevi pokazuje na drugi bajt u bufferu i odatle do kraja upisuje brojeve iz niza
	int *brojevi = (int *)(buffer + 1 * sizeof(char));
	for (int i = 0; i < n; i++) {
		brojevi[i] = niz[i];
	}

	// niz nam vise ne treba, sve je u bufferu
	free(niz);

	int *rezultat = CalculateMinMax(buffer);

	printf("\n");

	printf("Min je : %d\n", rezultat[0]);
	printf("Max je: %d\n", rezultat[1]);

	free(rezultat);

	return 0;
}
