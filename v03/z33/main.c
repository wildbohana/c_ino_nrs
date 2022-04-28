#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void copyLEToLE(int x, void* copy)
{
    for (int i = 0; i < sizeof(x); i++)
        *((char*) copy + i) = *((char*) &x + i);
}

void copyLEToBE(int x, void *copy)
{
    for (int i = 0; i < sizeof(x); i++)
        *((char*) copy + i) = *((char*) &x + sizeof(x) - i - 1);
}

int Count(char* buffer)
{
    int brojac = 0;
    char f = *buffer;

    short n = *(short*) (buffer + sizeof(char));

    double* brojevi = (double*) (buffer + sizeof(short) + sizeof(char));

    // vracanje iz BE u LE format
    if (f == 'B')
	{
        for (int i = 0; i < n; i++)
		{
            int br1 = brojevi[i];
            int br2 = brojevi[i + n];

            copyLEToBE(br1, &brojevi[i]);
            copyLEToBE(br2, &brojevi[i + n]);
        }
    }

    // trazenje koliko brojeva je vece u prvom nizu
    for (int i = 0; i < n; i++)
        if (brojevi[i] > brojevi[i + n])
        	brojac++;

    return brojac;
}

int main(void)
{
    short n;

    do {
        printf("Unesite broj elemenata niza: ");
        scanf("%hi", &n);
    } while (n <= 1);

    double* niz1 = (double*) malloc(sizeof(double) * n);
    double* niz2 = (double*) malloc(sizeof(double) * n);

    for (int i = 0; i < n; i++)
    {
        printf("niz1[%d]: ", i);
        scanf("%lf", (niz1 + i));
    }

    for (int i = 0; i < n; i++)
    {
        printf("niz2[%d]: ", i);
        scanf("%lf", (niz2 + i));
    }

    char *bafer = (char*) malloc(sizeof(char) + (short) + 2 * n * sizeof(double));

    char f;
    do {
        printf("Izbor formata [L/B]: ");
        scanf(" %c", &f);
    } while (f != 'L' && f != 'B');

    bafer[0] = f;
    *(short*) (bafer + 1) = n;

    double* brojevi = (double*) (bafer + 3);

    if (f == 'B')
	{
        for (int i = 0; i < n; i++)
		{
            int br1 = niz1[i];
            int br2 = niz2[i];

            copyLEToBE(br1, &niz1[i]);
            copyLEToBE(br2, &niz2[i]);
        }
    }
    else
	{
        for (int i = 0; i < n; i++)
		{
            int br1 = niz1[i];
            int br2 = niz2[i];

            copyLEToLE(br1, &niz1[i]);
            copyLEToLE(br2, &niz2[i]);
        }
    }

    // upis elemenata iz nizova u bafer
    int j = 0;

    for (int i = 0; i < n; i++)
        brojevi[j++] = niz1[i];

    for (int i = 0; i < n; i++)
        brojevi[j++] = niz2[i];

	int vecih = Count(bafer);
    printf("\nU prvom nizu ima %d vecih elemenata.", vecih);

    free(niz1);
    free(niz2);
    free(bafer);

    return 0;
}
