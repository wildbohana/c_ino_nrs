#include <stdio.h>
#include <stdlib.h>

int* CalculateMinMax(char* buffer)
{
    int* rez = (int*) malloc(2 * sizeof(int));
    int* niz = (int*) (buffer + sizeof(char));

    int n = (int) buffer[0];

    rez[0] = niz[0];    // min
    rez[1] = niz[0];    // max

    for (int i = 1; i < n; i++)
    {
        if (niz[i] < rez[0])
            rez[0] = niz[i];
        if (niz[i] > rez[1])
            rez[1] = niz[i];
    }

    return rez;
}

int main()
{
    short n;

    do {
        printf("Unesite broj n (n>0): ");
        scanf("%hi", &n);
    } while (n <= 0);

    // najbolje dinamicki niz ovde da se koristi
    int* niz = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("niz[%d]: ", i);
        scanf("%d", &niz[i]);
    }

    char* bafer = (char*) malloc(sizeof(char) + n * sizeof(int));

    bafer[0] = (char) n;
    int* brojevi = (int*) (bafer + sizeof(char));

    for (int i = 0; i < n; i++)
        brojevi[i] = niz[i];

    int* MiniMax = CalculateMinMax(bafer);
    printf("\nMinimum je: %d", MiniMax[0]);
    printf("\nMaksimum je: %d", MiniMax[1]);

    // oslobodi dinamicki alociranu memoriju
    free(niz);
    free(bafer);

    return 0;
}
