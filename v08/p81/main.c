/*
Potrebno je:
- definisati funkcijski tip za funkciju koja poredi dva broja tipa integer i vraća vrednost poređenja
- kreirati funkcije uporediManje() i uporediVece() koja vraća da li je prvi argument funkcije manji, odnosno veći od drugog argumenta
- kreirati funkciju za sortiranje niza N velih brojeva koja kao parametar prima i funkciju datog funkcijskog tipa.
  Primljeni parametar koristiti za poređenje brojeva pri sortiranju
- sortirati brojeve rastuće i opadajuće koristeći date funkcije

Definicija funkcijskog tipa:
typedef int poredjenje(int, int);
*/

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
	int i, j, t;
	for (j = n - 1; j > 0; j--)
    	for (i = 0; i < j; i++)
        	if ((*uporedi)(a[i + 1], a[i]))
            {
				t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
			}
}

int main()
{
	// unosimo broj n
    int n;
    printf("Unesi duzinu niza n: ");
    scanf("%d", &n);

	// unosimo niz
	printf("Unesi elemente niza jedan po jedan:\n");
    int i, a[n];
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

	// sortirano rastuce
    bubbleSort(a, n, uporediManje);
    printf("\nNiz sortiran rastuce izgleda ovako: \n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

	// sortirano opadajuce
    bubbleSort(a, n, uporediVece);
    printf("\nNiz sortiran opadajuce izgleda ovako: \n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
