/*
Neka je dat tip podatka ispit koji predstavlja podatke o polaganju ispita i koji je definisan u fajlu ispit.h. 
Napisati program koji učitava podatke tipa ispit o polaganju ispita za N studenata iz M predmeta i smešta ih u bafer, 
tako što na početak prvo stavi brojeve N i M tipa int, a zatim i sve podatke u pack(4) sistemu, koristeći direktan pristup baferu.
Podatke ispisati funkcijom ispisiPodatke(). 

Dodatno:
- šifru ispitnog roka učitavati kao string u osnovi 16. 
  U slučaju pogrešnog unosa, zatražiti ponovno učitavanje šifre. 
  Pod pogrešnim unosom se smatra unos pogrešnog znaka
- Napisati funkciju prebroj() koja prima bafer i funkciju f koja za jedan ispit vraća vrednost true/false i koja 
  broji za koliko ispita je zadovoljen uslov dat funkciom f. 
  Prebrojati sve ispite sa ocenom većom od 6.

typedef struct {
	short dan, mesec, godina;
	char ocena;
	int sifraIspRok;
	char profesor[30];
} ispit;
*/

#include <stdio.h>
#include <stdlib.h>
#include "ispit.h"
#pragma pack(4)

int main()
{
    char* buffer;

    //ispisPodatke(buffer);
	
    return 0;
}
