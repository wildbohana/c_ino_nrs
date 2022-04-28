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

int konverzija(char* string)
{
    int rez = 0;
    int i = 0;

    while(string[i] != 0)
    {
        if (string[i] >= '0' && string[i] <= '9')
            rez = rez * 16 + string[i] - '0';
        else if (string[i] >= 'A' && string[i] <= 'F')
            rez = rez * 16 + string[i] - 'A' + 10;
        else if (string[i] >= 'a' && string[i] <= 'f')
            rez = rez * 16 + string[i] - 'a' + 10;
        else
            return -1;

        i++;
    }

    return rez;
}

char* ucitavanjePodatakaIUpisUBuffer()
{
    int brojPredmeta;
    int brojStudenata;

    printf("\nUnesite broj predmeta: ");
    scanf("%d", &brojPredmeta);
    printf("\nUnesite broj studenata: ");
    scanf("%d", &brojStudenata);

    char* buffer = (char*) malloc(2 * sizeof(int) + brojPredmeta * brojStudenata * sizeof(ispit));

    *((int*) buffer) = brojStudenata;
    *((int*) (buffer + sizeof(int))) = brojPredmeta;

    for (int i = 0; i < brojPredmeta; i++)
    {
        for (int j = 0; j < brojStudenata; j++)
        {
            int hexSifra  = -1;

            short* dan = ((short*) (buffer + 2 * sizeof(int) + (i * brojStudenata + j) * sizeof(ispit)));
            short* mesec = ((short*) (buffer + 2 * sizeof(int) + (i * brojStudenata + j) * sizeof(ispit) + 2));
            short* godina = ((short*) (buffer + 2 * sizeof(int) + (i * brojStudenata + j) * sizeof(ispit) + 4));
            char* ocena = ((char*) (buffer + 2 * sizeof(int) + (i * brojStudenata + j) * sizeof(ispit) + 6));
            int* sifra = ((int*) (buffer + 2 * sizeof(int) + (i * brojStudenata + j) * sizeof(ispit) + 8));
            char* prof = ((char*) (buffer + 2 * sizeof(int) + (i * brojStudenata + j) * sizeof(ispit) + 12));

            printf("\nStudent[%d]", i + 1);

            printf("\n\tDan, Mesec, Godina: ");
            scanf("%hd %hd %hd", dan, mesec, godina);

            printf("\tOcena: ");
            scanf("%c", ocena);

            do {
                char sifraUnos[12];

                printf("\tSifra Ispitnog Roka: ");
                fflush(stdin);

                scanf(" %s", sifraUnos);
                printf("\n");

                hexSifra = konverzija(sifraUnos);
            } while (hexSifra == -1);

            *sifra = hexSifra;

            printf("\tProfesor: ");
            scanf("%s", prof);
        }
    }

    return buffer;
}

typedef int polozen(ispit);

int polozio(ispit isp)
{
    return isp.ocena > '5';
}

int prebroj(char* buffer, polozen p)
{
    int brojStudenata = *((int *) buffer);
    int brojPredmeta = *((int *)(buffer + sizeof(int)));

    int brojac = 0;

    ispit* isp = (ispit*) (buffer + 2 * sizeof(int));

    for (int j = 0; j < brojPredmeta; j++)
        for (int i = 0; i < brojStudenata; i++)
            if (p(isp[j * brojStudenata + i]))
                brojac++;

    return brojac;
}

int main(void)
{
    char* buffer = ucitavanjePodatakaIUpisUBuffer();

    ispisiPodatke(buffer);
    printf("\nBroj ispita koji zadovoljavaju uslov: %d ispit/a.\n", prebroj(buffer, polozio));

    return 0;
}
