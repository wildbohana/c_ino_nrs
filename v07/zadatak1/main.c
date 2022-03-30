#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    node *l;
    student st;
    int n, i;

    init(&l);

    // ucitavanje studenata
    printf("Unesite broj studenata: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Unesite podatke o studentu broj %d: \n", i + 1);
        scanf("%s%s%s%d", st.ime, st.prezime, st.brIndeksa, &st.brIspita);
        addBegin(l, st);
    }

    // ispis studenata
    node *t = l->next;
    while (t != l) {
        printf("%s\n", t->data.ime);
        printf("%s\n", t->data.prezime);
        printf("%s\n", t->data.brIndeksa);
        printf("%d\n", t->data.brIspita);
        t = t->next;
    }
	
    return 0;
}
