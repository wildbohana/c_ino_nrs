#include <stdio.h>
#include <stdlib.h>

typedef int provera(int);

int pozitivan(int  x)
{
	return (x >= 0);
}

int negativan(int  x)
{
	return (x < 0);
}

void ispisiNiz(int* a, int  n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);

	printf("\n");
}

int* izdvoj(int* buffer, provera* znakBroja)
{
    int brojac = 0;
    int niz[*buffer];

    for (int i = 0; i < *buffer; i++)
        if((*znakBroja) (*(buffer + i + 1)))
        {
            niz[brojac] = *(buffer + i + 1);
            brojac++;
        }

    int* izdvojeno = (int*) malloc(brojac * sizeof(int) + 1);

    *izdvojeno = brojac;

    for (int i = 0; i < brojac; i++)
        *(izdvojeno + i + 1) = niz[i];

    return izdvojeno;
}

void izdvajanje (int* buffer, char* string, provera* znakBroja)
{
    int* izdvojeno = izdvoj(buffer, znakBroja);
    int* tmp = izdvojeno;

    if (*tmp == 0)
        printf("\nNema %s brojeva!\n", string);
    else
    {
        printf("\nNiz %s brojeva: ", string);
        ispisiNiz(tmp + 1, *tmp);
    }

    free(izdvojeno);
}

int main(void)
{
    int n = 0;

    while (n < 1)
    {
        printf("Unesite velicinu niza: ");
        scanf("%d", &n);
    }

    int* buffer = (int*) malloc(n * sizeof(int) + 1);
    *buffer = n;

    printf("Unos elemenata niza:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", buffer + i + 1);

    izdvajanje(buffer, "pozitivnih", pozitivan);
    izdvajanje(buffer, "negativnih", negativan);

    return 0;
}
