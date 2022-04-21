/*
Koristeći kreirane funkcije, kreirati funkciju Calculate, koja prima bafer od 10 bajtova, od čega:
a) nulti bajt predstavlja slovo 'L' ili 'B', koji označava da li je broj dat u LE ili BE formatu
b) prvi bajt predstavlja operaciju (+, -, *, /)
c) preostalih 8 bajtova predstavljaju dva broja tipa integer, nad kojim je potrebno realizovati operaciju.

U slučaju da je nulti bajt 'L', brojevi su dati u LE formatu, a ako je nulti bajt 'B', broj je dat u BE formatu.
Povratna vrednost funkcije je tip podataka float koji sadrži rezultat u istom formatu.

Kreirati primer koji demonstrira rad kreiranih funkcija.

Zaglavlje funkcije Calculate dato je sa:
float Calculate(char* buffer);
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// samo prepišeš
void copyLEToLE(int x, void* copy) {
	for(int i = 0; i < sizeof(x); i++) {
		*((char*) copy + i) = *((char*) &x + i);
	}
}

// obrćeš
void copyLEToBE(int x, void* copy) {
	for(int i = 0; i < sizeof(x); i++) {
		*((char*) copy + i) = *((char*) &x + sizeof(x) - 1 - i);
	}
}

// funkcija za računanje
float Calculate(char* buffer) {
    char c = buffer[0];
    char op = buffer[1];
    int op1, op2;
    float rez;

    if (c == 'L') {
        copyLEToLE(*((int*) (buffer + 2)), &op1);
        copyLEToLE(*((int*) (buffer + 6)), &op2);
    } 
	else {
        copyLEToBE(*((int*) (buffer + 2)), &op1);
        copyLEToBE(*((int*) (buffer + 6)), &op2);
    }

    switch (op) {
        case '+': 
			rez = op1 + op2; break;
        case '-': 
			rez = op1 - op2; break;
        case '*': 
			rez = op1 * op2; break;
        case '/': 
			rez = op1 / op2; break;
    }

    if (c == 'L') {
        return rez;
    } 
	else {
        copyLEToBE(*((int*) &rez), &rez);
        return rez;
    }
}

int main()
{
    char c, op;
    int x, y;
    float rez;
    char buffer[2 * sizeof(char) + 2 * sizeof(int)];

	// unos L / B
    do {
        printf("Unesite format zapisa brojeva L ili B: ");
        scanf("%c", &c);
        fflush(stdin);
    } while (toupper(c) != 'L' && toupper(c) != 'B');

	// unos operacije
    do {
        printf("Unesite operaciju +, *, - ili /: ");
        scanf("%c", &op);
        fflush(stdin);
    } while (op != '+' && op != '-' && op != '*' && op != '/');

	// unos operanada
    printf("Unesite operande: ");
    scanf("%d %d", &x, &y);

	// određivanje da li je L ili B i poziv funkcije za računanje
    if (toupper(c) == 'L') {
        buffer[0] = 'L';
        buffer[1] = op;

        copyLEToLE(x, buffer + 2 * sizeof(char));
        copyLEToLE(y, buffer + 2 * sizeof(char) + sizeof(int));

        rez = Calculate(buffer);

        printf("Rezultat je %f", rez);
    } 
	else {
        buffer[0] = 'B';
        buffer[1] = op;

        copyLEToBE(x, buffer + 2 * sizeof(char));
        copyLEToBE(y, buffer + 2 * sizeof(char) + sizeof(int));

        rez = Calculate(buffer);

        copyLEToBE(*((int *) &rez), &rez);
        printf("Rezultat je %f", rez);
    }
	
    return 0;
}
