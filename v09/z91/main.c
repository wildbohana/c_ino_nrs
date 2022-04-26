/*
Neka je dat tip podatka izraz (definisan dole) u fajlu izraz.h, kao i bafer koji sadrži niz izraza A. 
Podaci se smeštaju u pack(4) sistemu. Bafer je moguće napraviti funkcijom napraviNiz(). 

Na početku bafera, nalazi se ukupan broj izraza N tipa integer, a zatim sledi N izraza.

Napisati funkciju izracunaj() koja čita podatke iz bafera direktnim pristupom baferu, 
izračunava svaki izraz (4 osnovne operacije, deljenje je celobrojno) i rezultat smešta nazad u bafer. 
Dati niz ispisati sa funkcijom ispisiNiz().

Napraviti funkciju izdvoj() koja sve rezultate izraza vraca u obliku liste. 
Definicija kružne liste data je u modulu lista (lista.h+lista.c).
Sve rezultate izraza smestiti u listu u big endian formatu.
Ispisati sve rezultate iz liste na ekran.

typedef struct {
	short broj1;
	char op;
	short broj2;
	int rezultat;
} izraz;
*/
#include <stdio.h>
#include <stdlib.h>

#include "izraz.h"
#include "list.h"

void izracunaj(char* buffer)
{
    int n = (int*) buffer[0];
	int rez;

	short br1, br2;
	char op;

	int velicina = sizeof(izraz);

	for (int i = 0; i < n; i++) {
		br1 = *((short*) (buffer + sizeof(int) + i * velicina));
		op = *(buffer + sizeof(int) + i * velicina + 2);
		br2 = *((short*) (buffer + sizeof(int) + i * velicina + 4));

		if (op == '+')
			rez = br1 + br2;
		else if (op == '-')
			rez = br1 - br2;
		else if (op == '*')
			rez = br1 * br2;
		else if (op == '/')
			rez = br1 / br2;
        else
            return 0;

		*((short*) (buffer + sizeof(int) + i * velicina + 8)) = rez;
	}
}

void copyLEToBE(int x, void* copy)
{
	for (int i = 0; i < sizeof(x); i++)
		*((char*) copy + i) = *((char*) &x + sizeof(x) - 1 - i);
}

node* izdvoj(char* buffer)
{
	int n = (int*) buffer[0];

	int rez;
	int rezBE;

	node* l;
	init(&l);

    int velicina = sizeof(izraz);

	for (int i = 0; i < n; i++){
		rez = *((short*) (buffer + sizeof(int) + i * velicina + 8));
		copyLEToBE(rez, &rezBE);

		addEnd(&l, rezBE);
	}

	return l;
};

int main()
{
    char* buffer = napraviNiz();

	ispisNiz(buffer);
	printf("\n");

	izracunaj(buffer);
	ispisNiz(buffer);
	printf("\n");

	node* l = izdvoj(buffer);
	node* temp = l -> next;

    int rez;
	int rezBE;

	printf("Rezultati izraza su: ");

	while (temp != l)
    {
		rezBE = temp -> data;
		copyLEToBE(rezBE, &rez);
		printf("%d ", rez);
		temp = temp -> next;
	}

    return 0;
}
