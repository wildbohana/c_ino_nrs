#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

float Calculate(char* buffer)
{
    float rez;

    char c = buffer[0];
    char o = buffer[1];

    int op1;
    int op2;

    // prva konverzija
    if (c == 'L')
    {
        copyLEtoLE(*((int*) (buffer + 2)), &op1);
        copyLEtoLE(*((int*) (buffer + 6)), &op2);
    }
    else
    {
        copyLEtoBE(*((int*) (buffer + 2)), &op1);
        copyLEtoBE(*((int*) (buffer + 6)), &op2);
    }

    // racunanje
    switch (o)
    {
        case '+': rez = (float) op1 + op2; break;
        case '-': rez = (float) op1 - op2; break;
        case '*': rez = (float) op1 * op2; break;
        case '/': rez = (float) op1 / op2; break;
    }

    // druga konverzija (ako je potrebno)
    if (c == 'L')
        return rez;
    else
    {
        copyLEtoBE(*((int*) &rez), &rez);
        return rez;
    }
}

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

int main()
{
    char f;
    char op;

    char* bafer = (char*) malloc(10 * sizeof(char));

    int op1;
    int op2;

    printf("Izaberite format [L/B]: ");
    scanf("%c", &f);
    fflush(stdin);

    printf("Izaberite operaciju [+, -, *, /]: ");
    scanf("%c", &op);
    fflush(stdin);

    printf("Unesi prvi operand: ");
    scanf("%d", &op1);
    printf("Unesi drugi operand: ");
    scanf("%d", &op2);

    if (toupper(f) == 'L')
    {
        bafer[0] = 'L';
        bafer[1] = op;

        copyLEtoLE(op1, bafer + 2);
        copyLEtoLE(op2, bafer + 6);

        float rezultat = Calculate(bafer);

        printf("Rezultat: %f", rezultat);
    }
    else
    {
        bafer[0] = 'B';
        bafer[1] = op;

        copyLEtoBE(op1, bafer + 2);
        copyLEtoBE(op2, bafer + 6);

        float rezultat = Calculate(bafer);

        copyLEtoBE(*((int*) & rezultat), &rezultat);
        printf("Rezultat: %f", rezultat);
    }

    free(bafer);

    return 0;
}
