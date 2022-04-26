#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void ispisiStudente(node* head)
{
    node* trenutni = head -> next;

    while(trenutni != head)
    {
        printf("\nIme: %s\n", trenutni -> data.ime);
        printf("Prezime: %s\n", trenutni -> data.prezime);
        printf("Indeks: %s\n", trenutni -> data.brojIndeksa);
        printf("Broj ispita: %d\n", trenutni -> data.brojIspita);

        trenutni = trenutni -> next;
    }
}

node* izdvoj(char* buffer)
{
    node* studenti;
    init(&studenti);

    student* tmp = (student*) (buffer + sizeof(int));

    int n = (int*) buffer[0];

    for (int i = 0; i < n; i++)
    {
        int brojIspita = tmp -> brojIspita;
        int j = 0;

        while (j < brojIspita)
        {
            if (strcmp(tmp -> ispiti[j].imeIspita, "NRS") == 0)
            {
                addBegin(studenti, *tmp);
                break;
            }
            j++;
        }

        tmp++;
    }

    return studenti;
}

int main(void)
{
    node* head;
    student st;
    int n;

    do
    {
        printf("Unesite broj studenata: ");
        scanf("%d", &n);
    } while(n < 1);

    char* buffer = (char*) malloc(n * sizeof(student) + sizeof(int));

    // alternativno: *((int*) buffer) = n;
    int* brStudenata = (int*) buffer;
    *brStudenata = n;

    student* upis = (student*) (buffer + sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("\nUnesite podatke o studentu broj %d: \n", i + 1);

        printf("\tIme: ");
        scanf("%s",  st.ime);
        printf("\tPrezime: ");
        scanf("%s",  st.prezime);
        printf("\tIndeks: ");
        scanf("%s",  st.brojIndeksa);
        printf("\tBroj ispita: ");
        scanf("%d", &st.brojIspita);

        printf("\n\t------- UNOS PODATAKA O ISPITIMA --------");
        for (int j = 0; j < st.brojIspita; j++)
        {
            printf("\n\tNaziv ispita: ");
            fflush(stdin);
            scanf("%20s", st.ispiti[j].imeIspita);

            printf("\tOcena: ");
            scanf("%hi", &st.ispiti[j].ocena);
        }

        upis[i] = st;
    }

    node* studenti = izdvoj(buffer);
    printf("\n--------------------- STUDENTI ---------------------\n");
    ispisiStudente(studenti);

    free(buffer);

    return 0;
}
