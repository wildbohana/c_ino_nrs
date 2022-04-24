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

// #include <ctype.h>

void copyLEtoLE(int x, void* copy)
{
    for (int i = 0; i < sizeof(x); i++)
        *((char*) copy + i) = *((char*) &x + i);
}

void copyLEtoBE(int x, void* copy)
{
    for (int i = 0; i < sizeof(x); i++)
        *((char*) copy + i) = *((char*) &x + sizeof(x) - 1 - i);
}

float Calculate(char* buffer)
{
    char format = buffer[0];
    char operacija = buffer[1];

    int op1, op2;
    float rez;

    if (format == 'L')
    {
        copyLEtoLE(*((int*) (buffer + 2)), &op1);
        copyLEtoLE(*((int*) (buffer + 6)), &op2);
    }
    else
    {
        copyLEtoBE(*((int*) (buffer + 2)), &op1);
        copyLEtoBE(*((int*) (buffer + 6)), &op2);
    }

    switch (operacija)
    {
        case '+':
            rez = op1 + op2; break;
        case '-':
            rez = op1 - op2; break;
        case '*':
            rez = op1 * op2; break;
        case '/':
            rez = op1 / op2; break;
    }

    if (format == 'L')
        return rez;
    else
    {
        copyLEtoBE(*((int*) &rez), &rez);
        return rez;
    }
}

int main()
{
    char format, operacija;
    int x, y;
    float rez;

    char bafer[2 * sizeof(char) + 2 * sizeof(int)];

    do {
        printf("Unesite format zapisa brojeva [L/B]: ");
        scanf("%c", &format);
        fflush(stdin);
    } while (toupper(format) != 'L' && toupper(format) != 'B');

    do {
        printf("Unesite operaciju [+, -, *, /]: ");
        scanf("%c", &operacija);
        fflush(stdin);
    } while (operacija != '+' && operacija != '-' && operacija != '*' && operacija != '/');

    printf("Unesite prvi operand: ");
    scanf("%d", &x);
    printf("Unesite drugi operand: ");
    scanf("%d", &y);

    if (toupper(format) == 'L')
    {
        bafer[0] = 'L';
        bafer[1] = operacija;

        copyLEtoLE(x, bafer + 2 * sizeof(char));
        copyLEtoLE(y, bafer + 2 * sizeof(char) + sizeof(int));

        rez = Calculate(bafer);
    }
    else
    {
        bafer[0] = 'B';
        bafer[1] = operacija;

        copyLEtoBE(x, bafer + 2 * sizeof(char));
        copyLEtoBE(y, bafer + 2 * sizeof(char) + sizeof(int));

        rez = Calculate(bafer);

        copyLEtoBE(*((int*) &rez), &rez);
    }

    printf("\nRezultat je: %f", rez);

    return 0;
}
