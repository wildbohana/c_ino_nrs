#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char* konverzija(int x)
{
    char s[33];
    char* rez;

    s[32] = 0;
    int num = 0;
    int mask = 1;

    // kopiras sve
    for (int i = 0; i < 32; i++)
    {
        if ((x & mask) == 0)
            s[31 - i] = '0';
        else
        {
            s[31 - i] = '1';
            num = i;
        }
        mask = mask << 1;
    }

    // onda kopiras bez viska nula
    rez = (char*) malloc(num + 2);
    memcpy(rez, &s[31 - num], num + 2);

    // memcpy(pok. na odrediste, pok. na izvor, koliko karaktera kopira)

    return rez;
}

int main()
{
    int x;

    printf("Unesite broj u dekadnom sistemu: ");
    scanf("%d", &x);

    char* rez = konverzija(x);

    printf("Broj u binarnom sistemu je: %s", rez);

    return 0;
}
