#include <stdio.h>
#include <stdlib.h>

typedef int poredjenje(int, int);

int uporediManje(int a, int b){
	return a < b;
}

int uporediVece(int a, int b){
	return a > b;
}

void bubbleSort(int a[], int n, poredjenje *uporedi) {
	int i, j, t;

	for (j = n - 1; j > 0; j--)
		for (i = 0; i < j; i++)
			if ((*uporedi)(a[i + 1], a[i])) {
				t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
			}
}

int main()
{
	int n;
	printf("Unesi broj n: ");
	scanf("%d", &n);

	int i, a[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	bubbleSort(a, n, uporediManje);
	printf("Niz sortiran rastuce izgleda ovako: \n");
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}

	bubbleSort(a, n, uporediVece);
	printf("\nNiz sortiran opadajuce izgleda ovako: \n");
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	
	return 0;
}
