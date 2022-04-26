#include <stdio.h>
#include <stdlib.h>

typedef int poredjenje(int, int);

int uporediManje(int a, int b)
{
    return a < b;
}

int uporediVece(int a, int b)
{
    return a > b;
}

void bubbleSort(int a[], int n, poredjenje* uporedi)
{
    int temp;

    for (int j = n - 1; j > 0; j--)
        for (int i = 0; i < j; i++)
            if ((*uporedi) (a[i + 1], a[i]))
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
    // nema smisla, no sens
}

int main()
{
    int n;
    printf("Unesite broj n: ");
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++)
    {
        printf("niz[%d]: ", i);
        scanf("%d", &a[i]);
    }

    bubbleSort(a, n, uporediManje);
    printf("\nNiz sortiran rastuce:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    bubbleSort(a, n, uporediVece);
    printf("\nNiz sortiran opadajuce:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
