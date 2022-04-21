/*
Napisati program koji učitava broj X tipa int i konvertuje ga i binarni sistem u obliku stringa.

Program treba da ima funkciju sa zaglavljem:
char* konverzija(int x);

Funkciju realizovati koristeći matematičke operacije / i % da bi se dobio traženi broj.
*/

#include <stdio.h>
#include <stdlib.h>

char* konverzija(int n){
	char s[33], *rez;
	s[32] = 0;
	int i = 31;

	do {
    	if (n % 2 == 0) {
    		s[i] = '0';
		}
    	else {
        	s[i] = '1';
		}

     	i--;
     	n = n / 2;
   	} while (n != 0);

   	rez = (char*) malloc(32 - i);
   	memcpy(rez, &s[i + 1], 32 - i);

   	return rez;
}

int main()
{
    int n;
    char* s;

    printf("Unesite dekadni broj koji treba kovertovati: ");
    scanf("%d", &n);
	
    s = konverzija(n);
    printf("Binarni broj izgleda ovako: %s\n", s);
	
    return 0;
}
