/*
Napisati program koji učitava broj X tipa int i konvertuje ga u binarni sistem u obliku stringa.

Program treba da ima funkciju sa zaglavljem:
char* konverzija(int x);

Funkciju realizovati Koristeći programiranja niskog nivoa, 
tako što će se bitovi rezultata čitati direktno iz broja X.
*/


#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char* konverzija(int x)
{
    char s[33];
    char* rez;

    int mask, num;

    s[32] = 0;      // \0
    mask = 1;
    num = 0;

    for (int i = 0; i < 32; i++)
    {
        if ((x & mask) == 0)
        {
            s[31 - i] = '0';
        }
        else
        {
            s[31 - i] = '1';
            num = i;
        }

        mask = mask << 1;
    }

    rez = (char*) malloc(num + 2);
    memcpy(rez, &s[31 - num], num + 2);

    return rez;
}

int main()
{
    int x;

    printf("Unesite broj za konverziju: ");
    scanf("%d", &x);

    char* broj;
    broj = konverzija(x);

    printf("Binarni broj izgleda ovako: %s\n", broj);

    return 0;
}
