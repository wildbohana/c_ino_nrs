/*
Napisati program koji unosi broj N i matricu A dimenzije NxN i izračunava njenu determinantu koristeći razvoj matrice po nultoj vrsti.
Program rešiti rekurzivno.

Razvoj matrice po i-toj vrsti: ~ formula ~

Matrica Bi,j predstavlja matricu koja se dobija od matrice A izbacivanjem i-te vrste i j-te kolone.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int izracunajDeterminantu(int* buffer){
    int n = buffer[0];

    if (n == 1) {
        return buffer[1];
	}
    else if (n == 2) {
        return buffer[1] * buffer[4] - buffer[2] * buffer[3];
    } 
	else {
        int i, j, kol, suma = 0;
        int A[n][n];

        for (j = 0; j < n; j++)
            for (i = 0; i < n; i++)
                A[j][i] = buffer[j * n + i + 1]; 		// +1 zbog N

        int buffer2[(n - 1) * (n - 1) + 1];
        buffer2[0] = n - 1;

        for (kol = 0; kol < n; kol++) {
            // razvoj po 0-toj vrsti, vrsta j == 0 se preskace
            // preskace se i kolona kol
            for (j = 1; j < n; j++)
                for (i = 0; i < n; i++)
                    if (i < kol)
                        buffer2[(j - 1) * (n - 1) + i + 1] = A[j][i];
                    else if (i > kol)
                        buffer2[(j - 1) * (n - 1) + (i - 1) + 1] = A[j][i];

            suma += pow(-1, kol) * A[0][kol] * izracunajDeterminantu(buffer2);
        }
        return suma;
    }
}

int main()
{
    int i, j, n;

    printf("Unesite dimenzije matrice: ");
    scanf("%d", &n);

    int A[n][n];

    printf("Unesite elemente matrice: ");
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++)
            scanf("%d", &A[j][i]);

    int buffer[n * n + 1];
    buffer[0] = n;

    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++)
            buffer[j * n + i + 1] = A[j][i]; 	// +1 je zbog broja N

    int rez = izracunajDeterminantu(buffer);
    printf("Determinanta matrice je: %d", rez);
	
    return 0;
}
