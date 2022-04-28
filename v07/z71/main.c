#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    node *l;
    init(&l);

    int n;
    printf("Unesite broj studenata: ");
    scanf("%d", &n);

    student st;

    for (int i = 0; i < n; i++)
    {
        printf("Unesite podatke o studentu broj %d: \n", i+1);
        scanf("%s%s%s%d", st.ime, st.prezime, st.brIndeksa, &st.brIspita);

        addEnd(&l, st);
        // addBegin(l, st);
    }

    node* temp = l -> next;

    while (temp != l)
    {
        printf("%s\n", temp -> data.ime);
        printf("%s\n", temp -> data.prezime);
        printf("%s\n", temp -> data.brIndeksa);
        printf("%d\n", temp -> data.brIspita);
        
        temp = temp -> next;
    }

    return 0;
}
