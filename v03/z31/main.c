#include <stdio.h>
#include <stdlib.h>

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
    int a = 0x012A5F87;
    int aLE, aBE;

    copyLEtoLE(a, &aLE);
    copyLEtoBE(a, &aBE);

    printf("Vrednost a u LE formatu: %08x\n", aLE);
    printf("Vrednost a u BE formatu: %08x\n", aBE);

    return 0;
}
