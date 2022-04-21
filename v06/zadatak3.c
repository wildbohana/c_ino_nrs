/*
Neka je data struktura podataka Osoba, kao što je prikazano dole.
Napisati funkciju ispisiStariju() koja prihvata niz bajtova koji sadrži podatke 
o dve osobe definisane tipom Osoba, i ispisuje podatke o osobi koja je starija.

Funkcija je data sledećim zaglavljem:
void ispisiStariju(char* buffer);

typedef struct {
	char ime[12];
	char prezime[12];
	char pol;
	short danR, mesecR, godinaR;
	char JMBG[14]:
} Osoba;
*/

#include <stdio.h>
#include <stdlib.h>

#pragma pack(4)

typedef struct {
	char ime[12];
	char prezime[12];
	char pol;
	short danR, mesecR, godinaR;
	char JMBG[14];
} Osoba;

void ispisiStariju(char buffer[]){
	short* dan1 = &buffer[26];
	short* mesec1 = &buffer[28];
	short* godina1 = &buffer[30];

	int velicina = sizeof(Osoba);

	short* dan2 = &buffer[26+velicina];
	short* mesec2 = &buffer[28+velicina];
	short* godina2 = &buffer[30+velicina];
	
	if (*godina1 < *godina2 || *godina1 == *godina2 && *mesec1 < *mesec2 || *godina1 == *godina2 && *mesec1 == *mesec2 && *dan1 < *dan2)
		printf("Ime: %s\nPrezime: %s\nPol: %c\nJMBG: %s", &buffer[0], &buffer[12], buffer[24], &buffer[32]);
	else
		printf("Ime: %s\nPrezime: %s\nPol: %c\nJMBG: %s", &buffer[0 + velicina], &buffer[12 + velicina], buffer[24 + velicina], &buffer[32 + velicina]);
}

int main()
{   
	Osoba os[2];
    os[0] = (Osoba) {"Jugoslav", "Jugovic", 'M', 1, 4, 2001, "0104001800043"};
    os[1] = (Osoba) {"Severina", "Severic", 'Z', 3, 2, 2002, "0302002805012"};

    ispisiStariju((char*) os);

    return 0;
}
