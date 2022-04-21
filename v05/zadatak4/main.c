/*
Napisati program koji učitava broj X u binarnom sistemu u obliku stringa i konvertuje taj broj u tip podataka int.

Program treba da ima funkciju sa zaglavljem:
int konverzija(char* s);

Funkciju realizovati koristeći programiranje niskog nivoa, 
tako što će se bitovi upisivati u rezultat korišćenjem programiranja niskog nivoa.
*/

#include <stdio.h>
#include <stdlib.h>

int konverzija(char* s) {
	int rez, mask, i;
	rez = 0;

	i = strlen(s) - 1;
	mask = 1;

	while (i >= 0) {
		if (s[i] == '1') {
			rez = rez | mask;
		}

		mask = mask << 1;
		i--;
	}

	return rez;
}

int main() {
	int x;
	char s[33];

	printf("Unesite broj koji treba kovertovati: ");
	scanf("%s", s);

	x = konverzija(s);
	printf("Dekadni broj izgleda ovako: %d\n", x);
	
	return 0;
}
