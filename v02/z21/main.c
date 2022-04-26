#include <stdio.h>
#include <stdlib.h>

enum operacija {sabiranje, oduzimanje, mnozenje, deljenje};

float* Calculate(char* buffer)
{
    float* rez = (float*) malloc(sizeof(float));

    char op = buffer[0];
    int* operandi = (int*) (buffer + 1);

    // pro tip: kastuj samo prvi operand u float
    switch (op)
    {
    case sabiranje:
        *rez = (float) operandi[0] + operandi[1];
        break;
    case oduzimanje:
        *rez = (float) operandi[0] - operandi[1];
        break;
    case mnozenje:
        *rez = (float) operandi[0] * operandi[1];
        break;
    case deljenje:
        *rez = (float) operandi[0] / operandi[1];
        break;
    }

    return rez;
}

int main()
{
    char op;
    char* bafer = (char*) malloc(sizeof(char) + 2 * sizeof(int));

    printf("Izbor operacije [+, - , *, /]: ");
    scanf("%c", &op);
    fflush(stdin);

    if (op == '+')
        bafer[0] = sabiranje;
    else if (op == '-')
        bafer[0] = oduzimanje;
    else if (op == '*')
        bafer[0] = mnozenje;
    else if (op == '/')
        bafer[0] = deljenje;
    else
        return 0;

    int* operandi = (int*) (bafer + 1);

    printf("Prvi operand: ");
    scanf("%d", &operandi[0]);
    printf("Drugi operand: ");
    scanf("%d", &operandi[1]);

    float* rezultat = Calculate(bafer);

    printf("\nRezultat operacije: %f", *rezultat);

    // opet si zaboravila da oslobodis -_-
    free(rezultat);
    free(bafer);

    return 0;
}
