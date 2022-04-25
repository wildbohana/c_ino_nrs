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

//list izdvoj(char* buffer);

int main()
{
    node* l;
    init(&l);

    student st;
    int n;

    printf("Unesite broj studenata: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Unesite podatke o studentu broj %d: \n", i+1);
        scanf("%s", st.ime);
        scanf("%s", st.prezime);
        scanf("%s", st.brIndeksa);
        scanf("%d", &st.brIspita);

        addBegin(l, st);
    }

    printf("\n");

    node* t = l->next;

    while (t != l) {
        printf("%s\n", t->data.ime);
        printf("%s\n", t->data.prezime);
        printf("%s\n", t->data.brIndeksa);
        printf("%d\n", t->data.brIspita);

        t = t->next;
    }

    return 0;
}
