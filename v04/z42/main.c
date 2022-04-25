/*
Napisati program koji učitava broj V u binarnom sistemu u obliku stringa i konvertuje taj broj u tip podataka int.

Program treba da ima funkciju sa zaglavljem:
int konverzije(char* s);

Funkciju realizovati koristeći matematičke operacije + i * da bi se dobio traženi broj.
*/

#include <stdio.h>
#include <stdlib.h>

int konverzija(char* s)
{
    int rez = 0;
    int i = 0;

    while (s[i] != 0)
    {
        rez = rez * 2 + s[i] - '0';
        i++;
    }

    return rez;
}

int main()
{
    int n;
    char s[20];

    printf("Unesite binaran broj koji treba konvertovati: ");
    scanf("%s", &s);

    n = konverzija(s);

    printf("Dobija se dekadni broj: %d", n);

    return 0;
}
