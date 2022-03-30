#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void copyLEToLE(int x, void *copy) {
   for(int i = 0; i < sizeof(x); i++) {
      *((char *)copy + i) = *((char *)&x + i);
   }
}

void copyLEToBE(int x, void *copy) {
   for(int i = 0; i < sizeof(x); i++) {
      *((char *)copy + i) = *((char *)&x + sizeof(x) - 1 - i);
   }
}

float Calculate(char *buffer) {
    char c = buffer[0];
    char op = buffer[1];
    int op1, op2;
    float rez;

    if (c == 'L') {
        copyLEToLE(*((int *)(buffer + 2)), &op1);
        copyLEToLE(*((int *)(buffer + 6)), &op2);
    } else {
        copyLEToBE(*((int *)(buffer + 2)), &op1);
        copyLEToBE(*((int *)(buffer + 6)), &op2);
    }

    switch (op) {
        case '+': rez = op1 + op2; break;
        case '-': rez = op1 - op2; break;
        case '*': rez = op1 * op2; break;
        case '/': rez = op1 / op2;
    }

    if (c == 'L') {
        return rez;
    } else {
        copyLEToBE(*((int *) &rez), &rez);
        return rez;
    }
}

int main()
{
    char c, op;
    int x, y;
    float rez;
    char buffer[2 * sizeof(char) + 2 * sizeof(int)];

    do {
        printf("Unesite format zapisa brojeva L ili B: ");
        scanf("%c", &c);
        fflush(stdin);
    } while (toupper(c) != 'L' && toupper(c) != 'B');

    do {
        printf("Unesite operaciju +, *, - ili /: ");
        scanf("%c", &op);
        fflush(stdin);
    } while (op != '+' && op != '-' && op != '*' && op != '/');

    printf("Unesite operande: ");
    scanf("%d %d", &x, &y);

    if (toupper(c) == 'L') {
        buffer[0] = 'L';
        buffer[1] = op;

        copyLEToLE(x, buffer + 2 * sizeof(char));
        copyLEToLE(y, buffer + 2 * sizeof(char) + sizeof(int));

        rez = Calculate(buffer);

        printf("Rezultat je %f", rez);
    } else {
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
