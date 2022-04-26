#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char* konverzija(int x)
{
    char s[33];
    char *rez;

    // 0 je u ascii \0 (NULL) - kraj niza
    s[32] = 0;
    int i = 31;

    do {
        if (x % 2 == 0)
            s[i] = '0';
        else
            s[i] = '1';

        i--;
        x = x / 2;
    } while (x != 0);

    rez = (char*) malloc(32 - i);
    memcpy(rez, &s[i + 1], 32 - i);

    // memcpy(pok. na odrediste, pok. na izvor, koliko karaktera kopira)

    return rez;
}

int main()
{
    int x;
    printf("Unesite broj x: ");
    scanf("%d", &x);

    char* binarno = konverzija(x);
    printf("Broj u binarnom formatu izgleda ovako:\n");
    printf("%s", binarno);

    return 0;
}
