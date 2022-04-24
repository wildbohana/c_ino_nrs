/*
U programskom jeziku C/C++ implementirati funkciju čija je deklaracija:
float* Calculate(char* buffer);

Funkcija kao parametar prima pokazivač na niz bajtova. Niz bajtova treba interpretirati kao na slici ispod. 
Prvi bajt predstavlja matematičke operacije (0 - sabiranje, 1 - oduzimanje, 2 - množenje, 3 - deljenje).
Naredna četiri bajta predstavljaju prvi operand tipa integer, nakon čega 
slede naredna četiri bajta koja predstavljaju drugi operand tipa integer.

Na osnovu podataka dobijenih u nizu, primeniti odgovarajuću matematičku operaciju na operande. 

Povratna vrednost funkcije predstavlja pokazivač na broj u pokretnom zarezu (float) 
koji se dobije kao rezultat matematičke operacije.

Napisati test program za ovu funkciju.
*/
#include <stdio.h>
#include <stdlib.h>

enum ko {sabiranje, oduzimanje, mnozenje, deljenje};

float* Calculate(char* buffer)
{
    int* operand = (int*) (buffer + 1);

    float* rez = NULL;
    rez = (float*) malloc(sizeof(float));

    switch (buffer[0])
    {
        case sabiranje:
            *rez = (float) (operand[0] + operand[1]);
            break;
        case oduzimanje:
            *rez = (float) (operand[0] - operand[1]);
            break;
        case mnozenje:
            *rez = (float) (operand[0] * operand[1]);
            break;
        case deljenje:
            *rez = (float) (operand[0] / operand[1]);
            break;
    }

    return rez;
}

int main()
{
    char operacija;

    printf("Izaberite operaciju [+, -, *, /]: ");
    scanf("%c", &operacija);
    fflush(stdin);
    // moras fflush da bi se stdin ispraznio odmah sad

    int op1;
    int op2;

    printf("Unesite prvi operand: ");
    scanf("%d", &op1);
    printf("Unesite drugi operand: ");
    scanf("%d", &op2);

    char* bafer = (char*) malloc(sizeof(char) + 2 * sizeof(int));

    if (operacija == '+')
        bafer[0] = sabiranje;
    else if (operacija == '-')
        bafer[0] = oduzimanje;
    else if (operacija == '*')
        bafer[0] = mnozenje;
    else if (operacija == '/')
        bafer[0] = deljenje;
    else
        return 0;

    // ovo ne zaboravi - pokazivac na int i na char ne funkcionisu isto
    int* operand = (int*) (bafer + sizeof(char));

    operand[0] = op1;
    operand[1] = op2;

    float* rezultat;

    rezultat = Calculate(bafer);
    printf("Resenje je: %f\n", *rezultat);

    // obavezno zbog malloc-a
    free(rezultat);
    free(bafer);

    return 0;
}

