/*
U programskom jeziku C/C++ implementirati funkciju čija je deklaracija:
float* Calculate(char* buffer);

Funkcija kao parametar prima pokazivač na niz bajtova. Niz bajtova treba interpretirati kao na slici ispod. 
Prvi bajt predstavlja matematičke operacije (0 - sabiranje, 1 - oduzimanje, 2 - množenje, 3 - deljenje).
Naredna četiri bajta predstavljaju prvi operand tipa integer, nakon čega 
slede naredna četiri bajta koja predstavljaju drugi operand tipa integer.

Na osnovu podataka dobijenih u nizu, primeniti odgovarajuću matematičku operaciju na operande. 

Povratna vrednost funkcije predstavlja pokazivač na broj u pokretnom zarezu (float) 
koji se dobije kao rezultat matematičke operacije.

Napisati test program za ovu funkciju.
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
