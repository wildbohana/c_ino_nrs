/*
Napraviti listu koja sadrži podatke o N studenata i smestiti kreiranu listu u bafer.
Za svakog studenta zapamtiti ime, prezime, broj indeksa i broj položenih ispita.
Napisati funkciju izdvoj() koja iz datog bafera izdvaja sve studente koji su položili više od 5 ispita.

Zaglavlje funkcije dato je na sledeći način:
list izdvoji(char* buffer);
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    node* l;
    init(&l);
    
    student st;
    int n, i;

    // ucitavanje studenata
    printf("Unesite broj studenata: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) 
    {
        printf("Unesite podatke o studentu broj %d: \n", i+1);
        scanf("%s%s%s%d", st.ime, st.prezime, st.brIndeksa, &st.brIspita);
        addEnd(l, st);
    }

    // ispis studenata iz kruzne liste
    node* t = l->next;
    while (t != l) 
    {
        printf("%s\n", t->data.ime);
        printf("%s\n", t->data.prezime);
        printf("%s\n", t->data.brIndeksa);
        printf("%d\n", t->data.brIspita);
        t = t->next;
    }
	
    return 0;
}
