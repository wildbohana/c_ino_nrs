#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int konverzija(char* s)
{
    int rez = 0;
    int i = 0;

    while (s[i] != 0)
    {
        rez = rez * 2 + s[i] - '0';
        i++;
    }

    return rez;
}

int main()
{
    char broj[20];

    printf("Unesite binaran broj za konverziju: ");
    scanf("%s", &broj);
    fflush(stdin);

    int x = konverzija(broj);

    printf("Broj u decimalnom formatu: %d", x);

    return 0;
}
