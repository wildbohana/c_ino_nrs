/*
Napisati program koji učitava broj N (N > 0) tipa short i niz od N brojeva tipa integer, 
pakuje broj N i unete brojeve u niz bajtova i prosleđuje dobijeni niz funkciji average() 
koja izračunava i vraća najmanju i najveću vrednost u nizu.

Zaglavlje funkcije average() dato je ispod:
int* CalculateMinMax(char* buffer);

Povratna vrednost funkcije je pokazivač na niz od dva podatka tipa integer koji 
predstavljaju najmanju i najveću vrednost u nizu.
*/

#include <stdio.h>
#include <stdlib.h>

int* CalculateMinMax(char* buffer)
{
    int* rez = (int*) malloc(2 * sizeof(int));
    int n = (int) buffer[0];

    // pokazivac na pocetak niza
    int* niz = (int*) (buffer + sizeof(char));

    rez[0] = niz[0];        // min
    rez[1] = niz[0];        // max

    for (int i = 0; i < n; i++) {
        if (niz[i] < rez[0])
            rez[0] = niz[i];
        if (niz[i] > rez[1])
            rez[1] = niz[i];
    }

    return rez;
}

int main()
{
    short n = -1;

    do {
        printf("Unesite broj N (N>0): ");
        scanf("%hi", &n);
    } while (n <= 0);

    int* niz = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("niz[%d] = ", i);
        scanf("%d", &niz[i]);
    }

    char* bafer = (char*) malloc(sizeof(char) + n * sizeof(int));
    bafer[0] = n;

    // pokazivac na elemente iz bafera
    int* brojevi = (int*) (bafer + 1 * sizeof(char));

    // ovde se preko brojeva posredno pristupa brojevima iz bafera
    for (int i = 0; i < n; i++) {
        brojevi[i] = niz[i];
    }

    // niz nam vise ne treba
    free(niz);

    int* rezultat = CalculateMinMax(bafer);

    printf("\n");

    printf("Min je: %d\n", rezultat[0]);
    printf("Max je: %d\n", rezultat[1]);

    // zbog malloca, YOU FORGOT AGAIN
    free(rezultat);

    return 0;
}
